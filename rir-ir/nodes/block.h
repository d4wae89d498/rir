#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H

# include <rir.h>

struct block 
{
    node node;

    block       *prev;
    block       *next;
    const char  *name;
    instr       *start;
    instr       *last;
    terminator  *exit;
};

static void *block_visit(block *self, node_visitor *vis, void *ctx) {
    printf("block: %s start: %p\n", self->name, (void*)self->start);
    trace();
    ((node*)self->start)->accept((node*)self->start, vis, ctx);
    return 0;
}

static block *Block(const char *name) {
    block *out = new(block, 
        .node = {
            .accept = (ir_node_method) &block_visit
        },
        .name = name,
        .start = 0,
        .last = 0,
        .exit = 0,
    );

    builder_begin_block(out);

    return out;
}

# define block(name) Block(name)

#endif // RIR_BLOCK_H