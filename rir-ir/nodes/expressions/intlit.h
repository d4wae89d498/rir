#ifndef RIR_INTLIT_H
# define RIR_INTLIT_H
# include <rir.h>

typedef struct intlit
{
    expr_base
    int value;
} intlit;

static value *IntLit(int n) 
{
    expr *e = new(intlit, .value = n);
    value *out = value(e);
    return out;
}

# define intlit(v) IntLit(v)

#endif // RIR_INTLIT_H