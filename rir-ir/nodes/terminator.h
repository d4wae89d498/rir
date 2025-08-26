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

#endif // RIR_TERMINATOR_H