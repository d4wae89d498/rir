#include "diag.h"
#include <rir.h>

node_visitor *print_visitor;

///////////////////////////////////////////////////////////////////////

static void *visit_function(function *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "function %s: \n", self->name);
    block *b = self->start;
    while (b) {
        dot(b->node, accept, visitor, ctx);
        b = b->next;
    }
    fprintf(ctx->ostream, "function end\n");
    return 0;
}

static void *visit_block(block *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "block%d: \n", self->id);
    instr *i = self->start;
    while (i) {
        dot(i->node, accept, visitor, ctx);
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream,"temp%i = ", self->id);
    dot(self->e->node, accept, visitor, ctx);
    fprintf(ctx->ostream,"\n");
    return 0;
}

static void *visit_arg(arg *self, node_visitor *visitor, print_visitor_ctx *ctx)
{
    TRACE;
    fprintf(ctx->ostream,"arg(%d)", self->n);
    return 0;
}

static void *visit_binop(binop *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream,"%s(temp%d, temp%d)", self->type, self->left->id, self->right->id);
    return 0;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream,"intlit(%d)", self->value);
    return 0;
}

static void *visit_strlit(strlit *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream,"strlit(\"");
    dump_cstr(ctx->ostream, self->value);
    fprintf(ctx->ostream, "\")");
    return 0;
}

static void *visit_resolve(resolve *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream,"resolve(\"");
    dump_cstr(ctx->ostream, self->symbol_name);
    fprintf(ctx->ostream, "\")");
    return 0;
}

static void *visit_call(call *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "call temp%d(", self->fp->id);
    unsigned i = 0;
    while (i < self->arg_count) {
        fprintf(ctx->ostream, "temp%d", self->args[i]->id);
        i += 1;
        if (i != self->arg_count) {
            fprintf(ctx->ostream, ", ");
        }
    }
    fprintf(ctx->ostream, ")");
    return 0;
}

static void *visit_jump(jump *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "jump block%d\n", self->dest->id);
    return 0;
}

static void *visit_ret(ret *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "ret temp%d\n", self->value->id);
    return 0;
}

static void *visit_when(when *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "when(temp%d, block%d, block%d)\n", self->cond->id, self->t->id, self->f->id);
    return 0;
}

static void *visit_var(var *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "init var%d\n", self->id);
    return 0;
}

static void *visit_deref(deref *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "var%d = deref tmp%d\n", self->dest->id, self->v->id);
    return 0;
}

static void *visit_load(load *self, node_visitor *visitor, print_visitor_ctx *ctx)
{
    TRACE;
    fprintf(ctx->ostream, "load var%d", self->v->id);
    return 0;
}

static void *visit_ref( ref *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "ref var%d", self->v->id);
    return 0;
}

static void *visit_store(store *self, node_visitor *visitor, print_visitor_ctx *ctx) 
{
    TRACE;
    fprintf(ctx->ostream, "var%d = temp%d\n", self->dest->id, self->v->id);
    return 0;
}

///////////////////////////////////////////////////////////////////////

void setup_print_visitor(void)
{
    TRACE;

    static node_visitor visitor;
    print_visitor = &visitor;


    if (!default_visitor) {
        error("default_visitor shall be built first.");
        exit(1);
    }
    visitor = node_visitor_clone(*default_visitor);

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

    ensure_visitor_completed("print", &visitor);
}