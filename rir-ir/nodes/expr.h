#ifndef RIR_EXPR_H
# define RIR_EXPR_H
# include "./../node.h"

# define expr_base               \
    const char *expr_type;       \

typedef struct expr 
{
    expr_base
} expr;

#endif // RIR_EXPR_H