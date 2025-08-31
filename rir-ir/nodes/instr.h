#ifndef RIR_INSTR_H
# define RIR_INSTR_H
# include "./../node.h"


struct instr 
{
    node            node;
    struct instr    *prev;
    struct instr    *next;
    const char      *type;
};

instr *Instr(instr *i) {
    builder_begin_instr(i);    
    return i;
}

# define instr(x) Instr(x)

#endif // RIR_INSTR_H