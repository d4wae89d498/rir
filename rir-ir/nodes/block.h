#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H

# include <rir.h>

struct block 
{
    node_base

    block       *prev;
    block       *next;
    const char  *name;
    instr       *start;
    instr       *last;
    terminator  *exit;
};

static void *block_visit(block *self, hmap *vis, void *ctx) {
    printf("block: %s start: %p\n", self->name, (void*)self->start);
    return 0;
}

static block *Block(const char *name) {
    block *out = new(block, 
        .name = name,
        .start = 0,
        .last = 0,
        .exit = 0,
        .accept = (ir_node_method) &block_visit
    );

    builder_begin_block(out);

    return out;
}

# define block(name) Block(name)

#endif // RIR_BLOCK_H