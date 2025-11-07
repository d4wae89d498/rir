#ifndef RIR_BLOCK_H
# define RIR_BLOCK_H
# include <rir.h>

struct __attribute__((packed)) block {
    node        node;
    block       *prev;
    block       *next;
    const char  *name;
    instr       *start;
    instr       *last;  // check later if its a terminator
};

visitable(node_visitor, node, block, self)

static block *block_new(const char *name) {
    return new(block, 
        .node = {
            .accept = &block_visit,
            .type = "block"
        },
        .name = name,
        .start = 0,
        .last = 0,
    );
}

static block *Block(const char *name) {
    block *out = block_new(name);
    builder_begin_block(out);
    return out;
}

# define block(name) Block(name)

#endif // RIR_BLOCK_H