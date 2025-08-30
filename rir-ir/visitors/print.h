
#ifndef RIR_PRINT_VISITOR_H
# define RIR_PRINT_VISITOR_H
# include <rir.h>

typedef struct target_ctx {
    int depth;
} target_ctx;

static hmap *print_visitor;

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
        ((node*) b)->accept((node*)b, print_visitor, ctx); 
        b = b->next;
    }
    return 0;
}

static void *visit_block(block *self, target_ctx *ctx) 
{
    printf("block %s: \n", self->name);
    instr *i = self->start;
    while (i) {
        ((node*) i)->accept((node*)i, print_visitor, ctx); 
        i = i->next;
    }
    return 0;
}

static void *visit_value(value *self, target_ctx *ctx) 
{
    printf("temp%i = ", self->id);
    ((node*) self->e)->accept((node*)self->e, print_visitor, ctx); 
    return 0;
}



#define print_visitor() PrintVisitor()

hmap* PrintVisitor() 
{
    // Create and attach visitor
    print_visitor = new(hmap, 0);
    *print_visitor = hmap_init();

# define visitor_method(W) \
    hmap_emplace(print_visitor, #W, (void*)(uintptr_t)& (visit_ ## W));
    // Visitor impl
    visitor_method(prog)
    visitor_method(function)
    visitor_method(block)
    visitor_method(value)
    // ... todo
#undef visitor_method


    return print_visitor;
}
#endif