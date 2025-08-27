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

#endif // RIR_INSTR_H