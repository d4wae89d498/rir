#include "./target.h"
#include "rir.h"

static node_visitor visitor;

static void *visit_prog(prog *self, print_target_ctx *ctx) 
{
    for (c_each(i, functions, self->functions))
        dot(i.ref->second->node, accept, &visitor, ctx);
    return 0;
}

static void *visit_function(function *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "function %s: \n", self->name);
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, &visitor, ctx); 
        b = b->next;
    }
    fprintf(ctx->ostream, "function end\n");
    return 0;
}

static void *visit_block(block *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "%s: \n", self->name);
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, print_visitor, ctx); 
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream,"temp%i = ", self->id);
    (&self->e->node)->accept(&self->e->node, &visitor, ctx); 
    fprintf(ctx->ostream,"\n");
    return 0;
}

static void *visit_arg(arg *self, print_target_ctx *ctx) {
    fprintf(ctx->ostream,"arg(%d)", self->n);
    return 0;
}

static void *visit_binop(binop *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream,"%s(temp%d, temp%d)", self->type, self->left->id, self->right->id);
    return 0;
}

static void *visit_intlit(intlit *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream,"intlit(%d)", self->value);
    return 0;
}

static void *visit_strlit(strlit *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream,"strlit(\"");
    dump_cstr_to(ctx->ostream, self->value);
    fprintf(ctx->ostream, "\")");
    return 0;
}

static void *visit_resolve(resolve *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream,"resolve(\"");
    dump_cstr_to(ctx->ostream, self->symbol_name);
    fprintf(ctx->ostream, "\")");
    return 0;
}

static void *visit_call(call *self, print_target_ctx *ctx) 
{
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

static void *visit_jump(jump *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "jump %s\n", self->dest->name);
    return 0;
}

static void *visit_ret(ret *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "ret temp%d\n", self->value->id);
    return 0;
}

static void *visit_when(when *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "when(temp%d, %s, %s)\n", self->cond->id, self->t->name, self->f->name);
    return 0;
}

static void *visit_var(var *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "init v%d\n", self->id);
    return 0;
}

static void *visit_deref(deref *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "v%d = deref tmp%d\n", self->dest->id, self->v->id);
    return 0;
}

static void *visit_load(load *self, print_target_ctx *ctx)
{
    fprintf(ctx->ostream, "load v%d", self->v->id);
    return 0;
}

static void *visit_ref(ref *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "ref v%d", self->v->id);
    return 0;
}

static void *visit_store(store *self, print_target_ctx *ctx) 
{
    fprintf(ctx->ostream, "v%d = temp%d\n", self->dest->id, self->v->id);
    return 0;
}

///////////////////////////////////////////////////////////////////////

node_visitor *print_visitor = &visitor;

void setup_print_target(Targets *targets)
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


    ensure_visitor_completed("print", &visitor);

    // register visitor
    Targets_emplace(targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .visitor = &visitor
    ));

}