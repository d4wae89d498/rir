#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

typedef struct jump
{
    terminator terminator;

    block *dest;
} jump;

void Jump(block *dest) {
    jump *self = new(jump, 
        .terminator = {
            .type = "jump"
        },
        .dest = dest, 
    );

    terminator(&self->terminator);
}

# define jump(d) Jump(d)


#endif // RIR_JUMP_H