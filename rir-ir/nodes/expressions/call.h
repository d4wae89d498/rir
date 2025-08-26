#ifndef RIR_CALL_H
# define RIR_CALL_H

# include "./../expr.h"

typedef struct call 
{
    expr_base
    void        *fp;
    void        **args;
    int         arg_count;
} call;

value *Call(value *addr, ...)
{
    return 0;
}

# define call(...) Call(__VA_ARGS__, 0);

#endif // RIR_CALL_H