#ifndef RIR_PROG_H
# define RIR_PROG_H
# include <rir.h>

struct   prog {
    node        node;
    functions   functions;
};

visitable(node_visitor, node, prog, self)

static prog *prog_new(void) {
    return new(prog, 
        .node = {
            .accept = &prog_visit,
            .type = "prog"
        },
        .functions = functions_init(),
    );
}


static prog *Prog(void) {
    prog *self = prog_new();
    builder_begin(self);
    return self;
}

# define prog() Prog()

#endif // RIR_PROG_H