#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H

# include <rir.h>

struct block 
{
    const char  *name;
    instr       *start;
    instr       *last;
    terminator  *exit;
};

static block *Block(const char *name) {
    block *out = new(block, 
        .name = name,
        .start = 0,
        .last = 0,
        .exit = 0
    );

    builder_begin_block(out);

    return out;
}

# define block(name) Block(name)

#endif // RIR_BLOCK_H