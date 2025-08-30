#ifndef RIR_PROG_H
# define RIR_PROG_H
# include "./../node.h"



typedef struct prog {
    node_base    

    hmap   functions;

} prog;

static void *prog_visit(node *self, hmap *vis, void *ctx) {
    trace();
    void* p = (hmap_find(vis, "prog").ref)->second;
    fprintf(stderr, "-> %p\n", p);
    ir_visitor_method f = (ir_visitor_method)(uintptr_t)p;
    trace();
    return f(self, ctx);
}

static prog *Prog() {
    prog *out = new(prog, 
        .functions = hmap_init(),
        .accept = &prog_visit
    );

    return out;
}
# define prog() Prog()




// by default ... we should call main ?

#endif // RIR_PROG_H