
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
    for(c_each(i, hmap, self->functions)) {
        printf("Function[%s] = \n", cstr_str(&(i.ref->first)));
        ((node*) i.ref->second)->accept((node*)i.ref->second, print_visitor, ctx);   // todo: make sure functions are node* (and everything else too...)

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
    printf("temp%d %s temp%d\n", self->left->id, self->type, self->right->id);
  //  ((node*) self)->accept((node*)self, print_visitor, ctx); 
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
    // ... todo
#undef visitor_method


    return print_visitor;
}
#endif