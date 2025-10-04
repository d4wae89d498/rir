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
    instr       *last;  // check later if its a terminator
};

static void *block_visit(block *self, node_visitor *vis, void *ctx) {
    return node_visitor_find(vis, "block").ref->second(
        &self->node,
        ctx
    );
}

static block *block_decl(const char *name) {
    return new(block, 
        .node = {
            .accept = (ir_node_method) &block_visit,
            .type = "block"
        },
        .name = name,
        .start = 0,
        .last = 0,
    );
}

static block *Block(const char *name) {
    block *out = block_decl(name);
    builder_begin_block(out);
    return out;
}
# define block(name) Block(name)

#endif // RIR_BLOCK_H