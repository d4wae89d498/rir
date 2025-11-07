#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

struct __attribute__((packed)) jump {
    terminator  terminator;
    block       *dest;
};

visitable(node_visitor, node, jump, self)

static jump *jump_new(block *dest) {
    return new(jump, 
        .terminator = terminator_impl(
            .accept = &jump_visit,
            .type = "jump"            
        ),
        .dest = dest
    );
}

static jump* Jump(block *dest) {
    jump *self = jump_new(dest);
    builder_attach_instr(&self->terminator.instr);
    return self;
}

# define jump(x) Jump(x)

#endif // RIR_jump_H