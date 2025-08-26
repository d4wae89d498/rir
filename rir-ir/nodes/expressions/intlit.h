#ifndef RIR_INTLIT_H
# define RIR_INTLIT_H

# include "./../expr.h"

typedef struct intlit
{
    expr_base
    int value;
} intlit;

static value *IntLit(const char *value) {
    return 0;
}

# define intlit(v) IntLit(v)

#endif // RIR_INTLIT_H