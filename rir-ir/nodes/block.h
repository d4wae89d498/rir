#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H
# include <rir.h>

struct  block {
    node        node;
    block       *prev;
    block       *next;
    int         id;
    instr       *start;
    instr       *last;  // check later if its a terminator
};

visitable(node_visitor, node, block, self)

static block *block_new(int id) {
    return new(block, 
        .node = {
            .accept = &block_visit,
            .type = "block"
        },
        .id = id,
        .start = 0,
        .last = 0,
    );
}

static block *Block(void) {
    block *out = block_new(block_id++);
    builder_begin_block(out);
    return out;
}

# define block() Block()

#endif // RIR_BLOCK_H