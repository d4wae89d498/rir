#include "./target.h"

node_visitor *print_visitor;

static void *visit_prog(prog *self, target_ctx *ctx) 
{
    for(c_each(i, functions, self->functions)) {
        i.ref->second->node.accept(&i.ref->second->node, print_visitor, ctx);   // todo: make sure functions are node* (and everything else too...)
    }
    return 0;
}

static void *visit_function(function *self, target_ctx *ctx) 
{
    printf("function %s: \n", self->name);
    block *b = self->start;
    while (b) {
        (&b->node)->accept(&b->node, print_visitor, ctx); 
        b = b->next;
    }
    printf("function end\n");
    return 0;
}

static void *visit_block(block *self, target_ctx *ctx) 
{
    printf("%s: \n", self->name);
    instr *i = self->start;
    while (i) {
        (&i->node)->accept(&i->node, print_visitor, ctx); 
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, target_ctx *ctx) 
{
    printf("temp%i = ", self->id);
    (&self->e->node)->accept(&self->e->node, print_visitor, ctx); 
    printf("\n");
    return 0;
}

static void *visit_arg(arg *self, target_ctx *ctx) {
    printf("arg(%d)", self->n);
    return 0;
}

static void *visit_binop(binop *self, target_ctx *ctx) 
{
    printf("%s(temp%d, temp%d)", self->type, self->left->id, self->right->id);
    return 0;
}

static void *visit_intlit(intlit *self, target_ctx *ctx) 
{
    printf("intlit(%d)", self->value);
    return 0;
}

static void *visit_strlit(strlit *self, target_ctx *ctx) 
{
    printf("strlit(\"%s\")", self->value);
    return 0;
}

static void *visit_resolve(resolve *self, target_ctx *ctx) 
{
    printf("resolve(\"%s\")", self->symbol_name);
    return 0;
}

static void *visit_call(call *self, target_ctx *ctx) 
{
    printf("call temp%d(", self->fp->id);
    unsigned i = 0;
    while (i < self->arg_count) {
        printf("temp%d", self->args[i]->id);
        i += 1;
        if (i != self->arg_count) {
            printf(", ");
        }
    }
    printf(")");
    return 0;
}

static void *visit_ret(ret *self, target_ctx *ctx) 
{
    printf(" ret temp%d\n", self->value->id);
    return 0;
}

static void *visit_when(when *self, target_ctx *ctx) 
{
    trace();
    printf("when(temp%d, %s, %s)\n", self->cond->id, self->t->name, self->f->name);
    return 0;
}

static void *visit_var(var *self, target_ctx *ctx) 
{
    printf("init v%d\n", self->id);
    return 0;
}

static void *visit_deref(deref *self, target_ctx *ctx) 
{
    printf("v%d = deref tmp%d\n", self->dest->id, self->v->id);
    return 0;
}

static void *visit_load(load *self, target_ctx *ctx)
{
    printf("load v%d", self->v->id);
    return 0;
}

static void *visit_ref(ref *self, target_ctx *ctx) 
{
    printf("ref v%d", self->v->id);
    return 0;
}

static void *visit_store(store *self, target_ctx *ctx) 
{
    printf("v%d = temp%d\n", self->dest->id, self->v->id);
    return 0;
}

void setup_print_target(Targets *targets)
{
    // Create and attach visitor
    print_visitor = new(node_visitor, 0);    
    *print_visitor = node_visitor_init();

    // Visitor impl
    node_visitor *vis = print_visitor;
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

    visitor_method(var)
    visitor_method(load)
    visitor_method(deref)
    visitor_method(ref)
    visitor_method(store)

    // register visitor
    Targets_emplace(targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .vis = print_visitor
    ));
}