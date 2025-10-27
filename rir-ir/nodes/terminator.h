#ifndef RIR_TERMINATOR_H
# define RIR_TERMINATOR_H
# include <rir.h>

struct terminator {
    instr       instr;
    node        impl;
};

visitable(node_visitor, node, terminator, &self->instr.impl)

static terminator TerminatorImpl(node impl) {
    return (terminator) {
        .instr = instr_impl(terminator_visit, "terminator"),
        .impl = impl
    };
}

# define terminator_impl(...) TerminatorImpl((node){__VA_ARGS__})

#endif // RIR_TERMINATOR_H