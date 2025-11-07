#ifndef RIR_PROG_H
# define RIR_PROG_H
# include <rir.h>

struct __attribute__((packed))  prog {
    node        node;
    functions   functions;
};

visitable(node_visitor, node, prog, self)

static prog *Prog(void) {
    return new(prog, 
        .node = {
            .accept = &prog_visit,
            .type = "prog"
        },
        .functions = functions_init(),
    );
}

# define prog() Prog()

#endif // RIR_PROG_H