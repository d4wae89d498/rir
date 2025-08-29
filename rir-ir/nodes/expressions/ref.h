#ifndef RIR_REF_H
# define RIR_REF_H
# include <rir.h>

static value *Ref(var *v) {
    v->var_type = V_STACK;
    value *out = new(value, 0);
    return out;
}

# define ref(x) Ref(x)

#endif // RIR_REF_H