#ifndef RIR_TERMINATOR_H
# define RIR_TERMINATOR_H
# include <rir.h>

struct terminator 
{
    instr       instr;
    const char  *type;
};

static instr* Terminator(terminator *t)
{
    t->instr.type = "terminator";
    block *b = builder_get_block();
    // todo if no b... error
    if (b->exit)
    {
        // TODO: error no 2x consecutive terminator in a block possible
    }
    else
    {
        if (!b->start) {
            b->start = &t->instr;
        }
        t->instr.prev = b->last;
        b->last = &t->instr;
        t->instr.next = 0;
    } 
    return (instr*) t;
} 

# define terminator(w) Terminator(w)

#endif // RIR_TERMINATOR_H