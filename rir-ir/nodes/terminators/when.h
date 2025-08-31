#ifndef RIR_WHEN_H
# define RIR_WHEN_H
# include <rir.h>

typedef struct when 
{
    terminator  terminator;
    expr        *cond;
    block       *t;
    block       *f;
} when;

#endif // RIR_WHEN_H