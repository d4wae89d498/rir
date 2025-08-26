#ifndef RIR_WHEN_H
# define RIR_WHEN_H
# include "./../terminator.h"
# include "./../expr.h"
# include "./../block.h"
# include "./../temp.h"

typedef struct when 
{
    terminator_base

    expr    *cond;
    block   *t;
    block   *f;
} when;

#endif // RIR_WHEN_H