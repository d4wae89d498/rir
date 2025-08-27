#ifndef RIR_TERMINATOR_H
# define RIR_TERMINATOR_H
# include <rir.h>

# define terminator_base        \
    instr_base                  \
    const char *terminator_type;

struct terminator 
{
   terminator_base
};

static instr* Terminator(terminator *t)
{
    t->instr_type = "terminator";
    block *b = builder_get_block();
    // todo if no b... error
    if (b->exit)
    {
        // TODO: error no 2x consecutive terminator in a block possible
    }
    else
    {
        if (!b->start) {
            b->start = (instr*) t;
        }
        t->prev = b->last;
        b->last = (instr*) t;
        t->next = 0;
    } 
    return (instr*) t;
} 

# define terminator(w) Terminator(w)

#endif // RIR_TERMINATOR_H