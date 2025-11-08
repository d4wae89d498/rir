#include "clone.h"
#include "rir.h"
#include "stcutils.h"

node_visitor *clone_visitor;

///////////////////////////////////////////////////////////////////////

static void *visit_prog(prog *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    prog *output = prog();
    builder_begin(output);
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, visitor, ctx);
    return output;
}

static void *visit_expr(expr *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_instr(instr *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_terminator(terminator *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->instr.node, visitor, ctx);
}

static void *visit_function(function *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    function *output = function_new(self->name);

    builder_begin_function(output);
    prog *current_prog = builder_get_prog();
    functions_emplace(&(current_prog->functions), self->name, output);

    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, visitor, ctx); 
        b = b->next;
    }
    return output;
}

static void *visit_block(block *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    block *output = block(self->name);
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, visitor, ctx); 
        i = i->next;
    }
    return output;
}

static void *visit_value(value *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value *output = value(dot(self->e->node, accept, visitor, ctx));   
    ptrmap_insert(&ctx->ptrmap, self, output);
    return output;
}

static void *visit_arg(arg *self, node_visitor *visitor, clone_visitor_ctx *ctx)
{
    TRACE;
    return arg(self->n);
}

static void *visit_binop(binop *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    ptrmap_iter l = ptrmap_find(&ctx->ptrmap, self->left);
    ptrmap_iter r = ptrmap_find(&ctx->ptrmap, self->right);
   
    if (!l.ref)
        error("Trying to clone a malformed LHS in a binop node.");
    if (!r.ref)
        error("Trying to clone a malformed RHS in a binop node.");
    if (!l.ref || !r.ref)
        exit(1);
    binop *e = new(binop,
        .expr = expr_impl(
            .accept = & ( binop_visit),
            .type = "binop",
        ),
        .type = self->type,
        .left = r.ref->second,
        .right = l.ref->second,
    );
    // value *val = value((expr*)e);
    //ptrmap_e
    // ptrmap_insert(&ctx->ptrmap, self, val);
    return e;//val;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return new(intlit, 
        .expr = self->expr,
        .value = self->value
    );
}

static void *visit_strlit(strlit *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return new(strlit, 
        .expr = self->expr,
        .value = strdup(self->value)
    );
}

static void *visit_resolve(resolve *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return resolve(self->symbol_name);
}

static void *visit_call(call *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    call *output = new(call,
        .expr = expr_impl(
            .accept = (ir_node_method) &call_visit,
            .type = "call"
        ),
        .fp = self->fp,
        .args = malloc(self->arg_count * sizeof(void*)),
        .arg_count = 0
    ); 

    int i = 0;
    while (i < self->arg_count)
    {
        printf("---\n");
        printf("expr.impl.type: %s\n", self->args[i]->e->impl.type);
        printf("expr.impl.accept: %p\n", (void*) self->args[i]->e->impl.accept);
        printf("node.type: %s\n",  self->args[i]->e->node.type);


        output->args[i] = dot(self->args[i]->e->node, accept, visitor, ctx);


        //output->args[i] = dot(self->args[i]->e->node, accept, &visitor, ctx);
        printf("done.\n");
        i += 1;
    }
    output->arg_count = i;
    
    return value(&output->expr);
}

static void *visit_jump(jump *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    block *dest = dot(self->dest->node, accept, visitor, ctx);
    return jump(dest);
}

static void *visit_ret(ret *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    ptrmap_iter v = ptrmap_find(&ctx->ptrmap, self->value);
    if (!v.ref) {
        error("Trying to ret an unknown temp");
        exit(1);
    }
    return ret(v.ref->second);
}

static void *visit_when(when *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value *cond = dot(self->cond->e->node, accept, visitor, ctx);
    block *t = dot(self->t->node, accept, visitor, ctx);
    block *f = dot(self->f->node, accept, visitor, ctx);
    return when(cond, t, f);
}

static void *visit_var(var *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    
    var *v = var();
    
    ptrmap_insert(&ctx->ptrmap, self, v);
    v->id = self->id;
    v->type = self->type;

    return v;
}

static void *visit_deref(deref *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value   *val = dot(self->v->e->node, accept, visitor, ctx);
    return deref(val);
}

static void *visit_load(load *self, node_visitor *visitor, clone_visitor_ctx *ctx)
{   
    TRACE;
    var *var = dot(self->v->instr.node, accept, visitor, ctx);
    return load(var);
}

static void *visit_ref(ref *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    var *var = dot(self->v->instr.node, accept, visitor, ctx);
    return ref(var);
}

static void *visit_store(store *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;

    ptrmap_iter dest = ptrmap_find(&ctx->ptrmap, self->dest);
    if (!dest.ref) {
        error("Storing unknown var");
        exit(1);
    }
    ptrmap_iter v = ptrmap_find(&ctx->ptrmap, self->v);
    if (!v.ref) {
        error("Storing unknown temp");
        exit(1);
    }

    return store(dest.ref->second, v.ref->second);
}

///////////////////////////////////////////////////////////////////////

void setup_clone_visitor(void)
{
    TRACE;

    static node_visitor visitor;
    clone_visitor = &visitor;

    if (!default_visitor) {
        // TODO: error, default shall be setup first
    }
    // Create and attach visitor
    printf("%p\n", default_visitor);
    visitor = node_visitor_clone(*default_visitor);

    visitor_method(prog)

    //visitor_method(expr)
    //visitor_method(instr)
    //visitor_method(terminator)

    visitor_method(function)
    visitor_method(block)
    visitor_method(value)
    visitor_method(binop)
    visitor_method(arg)
    visitor_method(intlit)
    visitor_method(strlit)
    visitor_method(resolve)
    visitor_method(call)
    visitor_method(ret)
    visitor_method(when)
    visitor_method(jump)

    visitor_method(var)
    visitor_method(load)
    visitor_method(deref)
    visitor_method(ref)
    visitor_method(store)


    ensure_visitor_completed("clone", &visitor);


}