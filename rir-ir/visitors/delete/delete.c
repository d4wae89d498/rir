#include "delete.h"
#include "stc/common.h"


node_visitor *delete_visitor;

///////////////////////////////////////////////////////////////////////

static void *visit_prog(prog *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, visitor, ctx);

    ptrset_insert(&ctx->ptrset, self);
    return 0;
}

static void *visit_expr(expr *self, node_visitor *visitor, delete_visitor_ctx *ctx) 
{
    TRACE;
    self->impl.accept(&self->node, visitor, ctx);
    ptrset_insert(&ctx->ptrset, self);
    return 0;
}

static void *visit_instr(instr *self, node_visitor *visitor, delete_visitor_ctx *ctx) 
{
    TRACE;
    self->impl.accept(&self->node, visitor, ctx);
    ptrset_insert(&ctx->ptrset, self);
    return 0;
}

static void *visit_terminator(terminator *self, node_visitor *visitor, delete_visitor_ctx *ctx) 
{
    TRACE;
    self->impl.accept(&self->instr.node, visitor, ctx);
    return 0;
}

static void *visit_function(function *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, visitor, ctx); 
        b = b->next;
    }
    ptrset_insert(&ctx->ptrset, self);
    return 0;
}

static void *visit_block(block *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, delete_visitor, ctx); 
        i = i->next;
    }
    ptrset_insert(&ctx->ptrset, self);
    return 0;
}

static void *visit_value(value *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    dot(self->e->node, accept, visitor, ctx); 
    return 0;
}

static void *visit_arg(arg *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_binop(binop *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    dot(self->left->e->node, accept, visitor, ctx);
    dot(self->right->e->node, accept, visitor, ctx);
    return 0;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_strlit(strlit *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    ptrset_insert(&ctx->ptrset, (void*)self->value);
    return 0;
}

static void *visit_resolve(resolve *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    ptrset_insert(&ctx->ptrset, (void*)self->symbol_name);
    return 0;
}

static void *visit_call(call *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    dot(self->fp->instr.node, accept, visitor, ctx);
    int i = 0;
    while (i < self->arg_count)
    {
        dot(self->args[i]->instr.node, accept, visitor, ctx);
        i += 1;    
    }
    return 0;
}

static void *visit_jump(jump *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_ret(ret *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_when(when *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_var(var *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_deref(deref *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_load(load *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_ref(ref *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

static void *visit_store(store *self, node_visitor *visitor, delete_visitor_ctx *ctx)
{
    TRACE;
    return 0;
}

///////////////////////////////////////////////////////////////////////

void delete_visitor_flush(delete_visitor_ctx *ctx) {
    for (c_each(i, ptrset, ctx->ptrset)) {
        free(*i.ref);
    }
}

//

void setup_delete_visitor(void)
{
    TRACE;

    printf("setup delete...\n");
    static node_visitor visitor;
    delete_visitor = &visitor;

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

    ensure_visitor_completed("delete", delete_visitor);
}