#ifndef RIR_PROG_H
# define RIR_PROG_H
# include <rir.h>

struct prog {
    node        node;
    functions   functions;
};

static void *prog_visit(node *self, node_visitor *vis, void *ctx) {
    trace();
    return (node_visitor_find(vis,  "prog").ref)->second(
        self,
        ctx
    );
}

static prog *Prog(void) {
    prog *out = new(prog, 
        .node = {
            .accept = &prog_visit
        },
        .functions = functions_init(),
    );

    return out;
}
# define prog() Prog()




// by default ... we should call main ?

#endif // RIR_PROG_H