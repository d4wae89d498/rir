
#ifndef RIR_PRINT_VISITOR_H
# define RIR_PRINT_VISITOR_H
# include <rir.h>

typedef struct target_ctx {
    int depth;
} target_ctx;

static node_visitor *print_visitor;

static void *visit_prog(prog *self, target_ctx *ctx) 
{
    printf("=== BEGIN OF RIR DEBUG DUMP ===\n");
    for(c_each(i, functions, self->functions)) {
        printf("Function[%s] = \n", cstr_str(&(i.ref->first)));
        i.ref->second->node.accept(&i.ref->second->node, print_visitor, ctx);   // todo: make sure functions are node* (and everything else too...)

    }
    printf("=== END OF RIR DEBUG DUMP ===\n");
    return 0;
}

static void *visit_function(function *self, target_ctx *ctx) 
{
    printf("function %s: \n", self->name);
    block *b = self->start;
    while (b) {
        printf(" -- block:\n");
        (&b->node)->accept(&b->node, print_visitor, ctx); 
        b = b->next;
    }
    printf("-- func end\n");
    return 0;
}

static void *visit_block(block *self, target_ctx *ctx) 
{
    printf("block %s: \n", self->name);
    instr *i = self->start;
    while (i) {
        printf(" -- instr:\n");
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
    printf("temp%d [%s] temp%d\n", self->left->id, self->type, self->right->id);
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
    printf(" temp%d(", self->fp->id);
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


#define print_visitor() PrintVisitor()

node_visitor* PrintVisitor() 
{
    // Create and attach visitor
    print_visitor = new(node_visitor, 0);
    *print_visitor = node_visitor_init();

# define visitor_method(W) \
    node_visitor_emplace(print_visitor, #W, (ir_visitor_method)& (visit_ ## W));
    // Visitor impl
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

    // ... todo
#undef visitor_method


    return print_visitor;
}

static void setup_print_target()
{
    Targets_emplace(&targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .vis = PrintVisitor()
    ));
}

#endif