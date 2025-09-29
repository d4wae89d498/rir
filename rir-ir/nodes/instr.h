#ifndef RIR_INSTR_H
# define RIR_INSTR_H
# include <rir.h>

struct instr 
{
    node            node;
    struct instr    *prev;
    struct instr    *next;
    const char      *type;
};

#endif // RIR_INSTR_H