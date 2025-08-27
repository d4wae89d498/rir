#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

typedef struct jump
{
    terminator_base

    block *dest;
} jump;

void Jump(block *dest) {
    terminator *self = new(jump, .dest = dest, .terminator_type = "jump");

    terminator(self);
}

# define jump(d) Jump(d)


#endif // RIR_JUMP_H