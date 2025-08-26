#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H

# include "./instr.h"
# include "./terminator.h"

typedef struct block 
{
    const char  *name;
    instr       *start;
    terminator  *end;
} block;

static void builder_begin_block(block*);

static block *Block(const char *name) {
    block *out = new(block, .name = name);

    builder_begin_block(out);

    return out;
}

# define block(name) Block(name)

#endif // RIR_BLOCK_H