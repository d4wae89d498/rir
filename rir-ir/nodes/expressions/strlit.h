#ifndef RIR_STRLIT_H
# define RIR_STRLIT_H

# include "./../expr.h"

typedef struct strlit
{
    expr expr;
    char *value;
} strlit;

static value *StrLit(const char *value) {
    return 0;
}

# define strlit(v) StrLit(v)

#endif // RIR_STRLIT_H