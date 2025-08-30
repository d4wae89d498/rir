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

instr *Instr(instr *i) {
    builder_begin_instr(i);    
    return i;
}

# define instr(x) Instr(x)

#endif // RIR_INSTR_H