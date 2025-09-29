#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H
# include <rir.h>

struct block 
{
    node        node;
    block       *prev;
    block       *next;
    const char  *name;
    instr       *start;
    instr       *last;  // TODO: maybe only have one instr* exit, and check later if its a terminator -- should make builder shorter?
    terminator  *exit;
};

static void *block_visit(block *self, node_visitor *vis, void *ctx) {
    return node_visitor_find(vis, "block").ref->second(
        &self->node,
        ctx
    );
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