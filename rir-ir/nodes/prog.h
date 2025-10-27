#ifndef RIR_PROG_H
# define RIR_PROG_H
# include <rir.h>

struct prog {
    node        node;
    functions   functions;
};

visitable(node_visitor, node, prog, self)

static prog *Prog(void) {
    prog *out = new(prog, 
        .node = {
            .accept = &prog_visit,
            .type = "prog"
        },
        .functions = functions_init(),
    );
    return out;
}

# define prog() Prog()

#endif // RIR_PROG_H