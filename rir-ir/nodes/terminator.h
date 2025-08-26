#ifndef RIR_TERMINATOR_H
# define RIR_TERMINATOR_H
# include "./instr.h"

# define terminator_base        \
    instr_base                  \
    char *terminator_type;

typedef struct terminator 
{
   terminator_base
} terminator;

static void Terminate(terminator *t)
{
    block *b = builder_get_block();
    // todo if no b... error
    if (b->exit)
    {
        // error no 2x consecutive terminator in a block possible
    }
    else
    {
        out->prev = b->last;
        b->last = out;
    } 
} 

#endif // RIR_TERMINATOR_H