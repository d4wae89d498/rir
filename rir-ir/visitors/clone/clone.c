#include "clone.h"
#include "rir.h"
#include "stcutils.h"

node_visitor *clone_visitor;


///////////////////////////////////////////////////////////////////////

static block *clone_block_ref(clone_visitor_ctx *ctx, block *b) {
    block *output = ptrmap_hit(&ctx->ptrmap, b);
    if (output)
        return output;
    output = block_new(b->id);
    ptrmap_insert(&ctx->ptrmap, b, output);
    return output;
}

static void *visit_prog(prog *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    prog *output = prog();
    builder_begin(output);
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, visitor, ctx);
    return output;
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

    block *output = clone_block_ref(ctx, self);

    builder_begin_block(output);

    instr *i = self->start;
    while (i) {
        instr *clonned_instr = (&i->node)->accept(&i->node, visitor, ctx); 
        builder_attach_instr(clonned_instr);

        i = i->next;
    }
    return output;
}

static void *visit_value(value *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    expr *e = dot(self->e->node, accept, visitor, ctx);
    value *output = value_new(self->id, e);   
    ptrmap_insert(&ctx->ptrmap, self, output);
    return output;
}

static void *visit_arg(arg *self, node_visitor *visitor, clone_visitor_ctx *ctx)
{
    TRACE;
    return arg_new(self->n);
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
        .left = l.ref->second,
        .right = r.ref->second,
    );
    return e;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return intlit_new(self->value);
}

static void *visit_strlit(strlit *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return strlit_new(strdup(self->value));
}

static void *visit_resolve(resolve *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    return resolve_new(strdup(self->symbol_name));
}

static void *visit_call(call *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    call *output = new(call,
        .expr = expr_impl(
            .accept = (node_method) &call_visit,
            .type = "call"
        ),
        .fp = self->fp,
        .args = malloc(self->arg_count * sizeof(void*)),
        .arg_count = 0
    ); 
    int i = 0;
    while (i < self->arg_count)
    {
        ptrmap_iter arg_at_i = ptrmap_find(&ctx->ptrmap, self->args[i]);
        if (!arg_at_i.ref) {
            error("Trying to call using an unknown arg at pos %d", i);
            exit(1);
        }
        output->args[i] = arg_at_i.ref->second;
        i += 1;
    }
    output->arg_count = i;
    return output;
}

static void *visit_jump(jump *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;

    block *dest = clone_block_ref(ctx, self->dest);

    return jump_new(dest);
}

static void *visit_ret(ret *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value *v = ptrmap_hit(&ctx->ptrmap, self->value);
    if (!v) {
        error("Trying to ret an unknown temp");
        exit(1);
    }
    return ret_new(v);
}

static void *visit_when(when *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value *cond = ptrmap_hit(&ctx->ptrmap, self->cond);
    if (!cond) {
        error("Trying to jump when with an unknown cond");
        exit(1);
    }

    block *t = clone_block_ref(ctx, self->t);
    block *f = clone_block_ref(ctx, self->f);
    
    return when_new(cond, t, f);
}

static void *visit_var(var *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    
    var *v = var_new(self->id);
    
    ptrmap_insert(&ctx->ptrmap, self, v);
    v->type = self->type;

    return v;
}

static void *visit_deref(deref *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    value *f = ptrmap_hit(&ctx->ptrmap, self->v);
    if (!f) {
        error("Trying to deref an unknown temp");
        exit(1);
    }
    return  deref_new(var_new(self->dest->id), f);
}

static void *visit_load(load *self, node_visitor *visitor, clone_visitor_ctx *ctx)
{   
    TRACE;
    var *v = ptrmap_hit(&ctx->ptrmap, self->v);
    if (!v) {
        error("Trying to load an unknown var");
        exit(1);
    }
    return load_new(v);
}

static void *visit_ref(ref *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;
    var *v = ptrmap_hit(&ctx->ptrmap, v);
    if (!v) {
        error("Trying to ref an unknown var");
        exit(1);
    }
    return ref_new(v);
}

static void *visit_store(store *self, node_visitor *visitor, clone_visitor_ctx *ctx) 
{
    TRACE;

    var *dest = ptrmap_hit(&ctx->ptrmap, self->dest);
    if (!dest) {
        error("Storing unknown var");
        exit(1);
    }

    value *temp = ptrmap_hit(&ctx->ptrmap, self->v);
    if (!temp) {
        error("Storing unknown temp");
        exit(1);
    }

    return store_new(dest, temp);
}

///////////////////////////////////////////////////////////////////////

void setup_clone_visitor(void)
{
    TRACE;

    static node_visitor visitor;
    clone_visitor = &visitor;

    if (!default_visitor) {
        error("default_visitor shall be built first.");
        exit(1);
    }
    visitor = node_visitor_clone(*default_visitor);

    visitor_method(prog)

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