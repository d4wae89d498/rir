#include "default.h"

node_visitor *default_visitor;

///////////////////////////////////////////////////////////////////////

static void *visit_prog(prog *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, visitor, ctx);
    return 0;
}

static void *visit_expr(expr *self, node_visitor *visitor, void *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_instr(instr *self, node_visitor *visitor, void *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_terminator(terminator *self, node_visitor *visitor, void *ctx) 
{
    TRACE;
    return self->impl.accept(&self->instr.node, visitor, ctx);
}

static void *visit_function(function *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, visitor, ctx); 
        b = b->next;
    }
    return 0;
}

static void *visit_block(block *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, visitor, ctx); 
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    dot(self->e->node, accept, visitor, ctx); 
    return 0;
}

static void *visit_arg(arg *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_binop(binop *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    dot(self->left->e->node, accept, visitor, ctx);
    dot(self->right->e->node, accept, visitor, ctx);
    return 0;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_strlit(strlit *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_resolve(resolve *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_call(call *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_jump(jump *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_ret(ret *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_when(when *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_var(var *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_deref(deref *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_load(load *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_ref(ref *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

static void *visit_store(store *self, node_visitor *visitor, void *ctx)
{
    TRACE;
    return 0;
}

///////////////////////////////////////////////////////////////////////

void setup_default_visitor(void)
{
    TRACE;

    printf("setup default visitor...\n");
    static node_visitor visitor;
    default_visitor = &visitor;

    // Create and attach visitor
    visitor = node_visitor_init();

    visitor_method(prog)

    visitor_method(expr)
    visitor_method(instr)
    visitor_method(terminator)

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

    ensure_visitor_completed("default", default_visitor);
}