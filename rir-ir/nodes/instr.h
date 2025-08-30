#ifndef RIR_INSTR_H
# define RIR_INSTR_H
# include "./../node.h"

# define instr_base             \
    node_base                   \
    struct instr *prev;         \
    struct instr *next;         \
    const char *instr_type;     \

struct instr 
{
    instr_base
};

instr *Instr(instr *out) {
    block *b = builder_get_block();
    // TODO: if (b == NULL) Error
    if (!b->start)
    {
        b->start = b->last =  out;
    }
    else
    {
        out->prev = b->last;
        b->last = out;
    }
    return out;
}

# define instr(x) Instr(x)

#endif // RIR_INSTR_H