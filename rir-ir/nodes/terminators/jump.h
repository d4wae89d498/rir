#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

struct jump {
    terminator  terminator;
    block       *dest;
};

visitable(node_visitor, node, jump, &self->terminator.impl)

static jump *jump_new(block *dest) {
    jump *self = new(jump, 
        .terminator = terminator_impl(
            .accept = &jump_visit,
            .type = "jump"            
        ),
        .dest = dest
    );
    builder_attach_instr(&self->terminator.instr); 
    return self;
}

# define jump(x) jump_new(x)

#endif // RIR_jump_H