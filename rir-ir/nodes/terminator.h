#ifndef RIR_TERMINATOR_H
# define RIR_TERMINATOR_H
# include <rir.h>

struct  terminator {
    instr       instr;
    node        impl;
};

visitable(node_visitor, node, terminator, self)

static terminator TerminatorImpl(node impl) {
    return (terminator) {
        .instr = instr_impl(
            .accept = &terminator_visit, 
            .type = "terminator"
        ),
        .impl = impl
    };
}

# define terminator_impl(...) TerminatorImpl((node){__VA_ARGS__})

#endif // RIR_TERMINATOR_H