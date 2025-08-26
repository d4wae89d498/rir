#ifndef RIR_RESOLVE_H
# define RIR_RESOLVE_H
# include "./../expr.h"

typedef struct resolve {
    expr_base

    prog    *prog;
    char    *symbol_name;
} resolve;


value *Resolve(const char *name) {
    return 0;
}

# define resolve(name) Resolve(name)

#endif // RIR_RESOLVE_H