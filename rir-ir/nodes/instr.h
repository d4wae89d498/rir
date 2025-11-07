#ifndef RIR_INSTR_H
# define RIR_INSTR_H
# include <rir.h>

struct __attribute__((packed)) instr {
    node            node;
    struct instr    *prev;
    struct instr    *next;
    node            impl;
};

visitable(node_visitor, node, instr, self)

static instr InstrImpl(node impl) {
    return (instr) {
        .node = (node) {
            .accept = &instr_visit,
            .type = "instr"
        },
        .next = 0,
        .prev = 0,
        .impl = impl
    };
}

# define instr_impl(...) InstrImpl((node){__VA_ARGS__})

#endif // RIR_INSTR_H