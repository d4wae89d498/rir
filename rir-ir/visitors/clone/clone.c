#include "clone.h"
#include "rir.h"

static node_visitor visitor;

static void *visit_prog(prog *self, void *ctx) 
{
    TRACE
    prog *output = prog();
    builder_begin(output);
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, &visitor, ctx);
    return output;
}

static void *visit_function(function *self, void *ctx) 
{
    TRACE
    function *output = function(self->name);
    TRACE
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, &visitor, ctx); 
        b = b->next;
    }
    return output;
}

static void *visit_block(block *self, void *ctx) 
{
    TRACE
    block *output = block(self->name);
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, &visitor, ctx); 
        i = i->next;
    }
    return output;
}

static void *visit_value(value *self, void *ctx) 
{
    TRACE
    return (&self->e->node)->accept(&self->e->node, &visitor, ctx); 
}

static void *visit_arg(arg *self, void *ctx)
{
    TRACE
    return arg(self->n);
}

static void *visit_binop(binop *self, void *ctx) 
{
    binop *output = new(binop,
        .expr = {
            .node = {
                .accept = (ir_node_method) & ( binop_accept ),
                .type = "expr"
            },
            .type = "binop",
        },
        .type = self->type,
        .left = dot(self->left->e->node, accept, &visitor, ctx),
        .right = dot(self->right->e->node, accept, &visitor, ctx),
    );
    return value((expr*)output);
}

static void *visit_intlit(intlit *self, void *ctx) 
{
    TRACE
    return intlit(self->value);
}

static void *visit_strlit(strlit *self, void *ctx) 
{
    TRACE
    return strlit(self->value);
}

static void *visit_resolve(resolve *self, void *ctx) 
{
    TRACE
    return resolve(self->symbol_name);
}

static void *visit_call(call *self, void *ctx) 
{
    TRACE
    call *output = new(call,
        .expr = {
            .node = {
                .accept = (ir_node_method) &call_visit,
                .type = "expr"
            },
            .type = "call"
        },
        .fp = self->fp,
        .args = malloc(self->arg_count * sizeof(void*)),
        .arg_count = 0
    ); 

    int i = 0;
    while (i < self->arg_count)
    {
        printf("---\n");
        printf("expr.type: %s\n", self->args[i]->e->type);
        printf("node.accept: %p\n", (void*) self->args[i]->e->node.accept);
        printf("node.type: %s\n",  self->args[i]->e->node.type);


        output->args[i] = dot(self->args[i]->e->node, accept, &visitor, ctx);


        //output->args[i] = dot(self->args[i]->e->node, accept, &visitor, ctx);
        printf("done.\n");
        i += 1;
    }
    output->arg_count = i;
    
    return value(&output->expr);
}


// todo : use block id to jump correctly...
// check if clone with args above works... 
// issue: it may be clonned twice..
static void *visit_jump(jump *self, void *ctx) 
{
    TRACE
    block *dest = dot(self->dest->node, accept, &visitor, ctx);
    jump(dest);
    return 0; // not an expr
}

static void *visit_ret(ret *self, void *ctx) 
{
    TRACE
    value *val = dot(self->value->e->node, accept, &visitor, ctx);
    ret(val);
    return 0; // not an expr
}

static void *visit_when(when *self, void *ctx) 
{
    TRACE
    value *cond = dot(self->cond->e->node, accept, &visitor, ctx);
    block *t = dot(self->t->node, accept, &visitor, ctx);
    block *f = dot(self->f->node, accept, &visitor, ctx);
    when(cond, t, f);
    return 0; // not an expr
}

static void *visit_var(var *self, void *ctx) 
{
    TRACE
    var *v = var();
    v->id = self->id;
    v->type = self->type;
    return v;
}

static void *visit_deref(deref *self, void *ctx) 
{
    TRACE
    value   *val = dot(self->v->e->node, accept, &visitor, ctx);
    return deref(val);
}

static void *visit_load(load *self, void *ctx)
{   
    TRACE
    var *var = dot(self->v->instr.node, accept, &visitor, ctx);
    return load(var);
}

static void *visit_ref(ref *self, void *ctx) 
{
    TRACE
    var *var = dot(self->v->instr.node, accept, &visitor, ctx);
    return ref(var);
}

static void *visit_store(store *self, void *ctx) 
{
    TRACE
    var *dest = dot(self->dest->instr.node, accept, &visitor, ctx);
    value *val = dot(self->v->e->node, accept, &visitor, ctx);
    store(dest, val);
    return 0; // not an expr 
}

///////////////////////////////////////////////////////////////////////

node_visitor *clone_visitor = &visitor;

void setup_clone_visitor(void)
{
    // Create and attach visitor
    visitor = node_visitor_init();

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