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
        printf("error !! exit already set ??\n");
        // TODO: error no 2x consecutive terminator in a block possible
    }
    else
    {
        builder_begin_instr(&t->instr);
    } 
    return (instr*) t;
} 

# define terminator(w) Terminator(w)

#endif // RIR_TERMINATOR_H