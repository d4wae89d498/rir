#ifndef RIR_ARG_H
# define RIR_ARG_H

# include "./../expr.h"

typedef struct arg
{
    expr_base
    unsigned n;
} arg;

static value *Arg(unsigned n) {
    return 0;
}

# define arg(n) Arg(n)

#endif // RIR_ARG_H