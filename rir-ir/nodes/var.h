#ifndef RIR_VAR_H
# define RIR_VAR_H
# include <rir.h>

typedef struct var {
    const char *name;
} var;

static var *Var(const char *name) {
    var *out = new(var, .name = name);
    return out;
}

# define var(n) Var(n)


#endif // RIR_VAR_H