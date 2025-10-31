#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

struct jump {
    terminator  terminator;
    block       *dest;
};

visitable(node_visitor, node, jump, &self->terminator.impl)

static jump *jump_new(block *dest) {
    return new(jump, 
        .terminator = terminator_impl(
            .accept = &jump_visit,
            .type = "jump"            
        ),
        .dest = dest
    );
}

# define jump(x) builder_attach_instr(&jump_new(x)->terminator.instr)

#endif // RIR_jump_H