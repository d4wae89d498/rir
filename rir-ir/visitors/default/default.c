#include "default.h"

static node_visitor visitor;

static void *visit_prog(prog *self, void *ctx) 
{
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, &visitor, ctx);
    return 0;
}

static void *visit_function(function *self, void *ctx) 
{
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, &visitor, ctx); 
        b = b->next;
    }
    return 0;
}

static void *visit_block(block *self, void *ctx) 
{
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, default_visitor, ctx); 
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, void *ctx) 
{
    dot(self->e->node, accept, &visitor, ctx); 
    return 0;
}

static void *visit_arg(arg *self, void *ctx) {
    return 0;
}

static void *visit_binop(binop *self, void *ctx) 
{
    dot(self->left->e->node, accept, &visitor, ctx);
    dot(self->right->e->node, accept, &visitor, ctx);
    return 0;
}

static void *visit_intlit(intlit *self, void *ctx) 
{
    return 0;
}

static void *visit_strlit(strlit *self, void *ctx) 
{
    return 0;
}

static void *visit_resolve(resolve *self, void *ctx) 
{
    return 0;
}

static void *visit_call(call *self, void *ctx) 
{
    return 0;
}

static void *visit_jump(jump *self, void *ctx) 
{
    return 0;
}

static void *visit_ret(ret *self, void *ctx) 
{
    return 0;
}

static void *visit_when(when *self, void *ctx) 
{
    return 0;
}

static void *visit_var(var *self, void *ctx) 
{
    return 0;
}

static void *visit_deref(deref *self, void *ctx) 
{
    return 0;
}

static void *visit_load(load *self, void *ctx)
{
    return 0;
}

static void *visit_ref(ref *self, void *ctx) 
{
    return 0;
}

static void *visit_store(store *self, void *ctx) 
{
    return 0;
}

///////////////////////////////////////////////////////////////////////

node_visitor *default_visitor = &visitor;

void setup_default_visitor(void)
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


    ensure_visitor_completed("default", &visitor);


}