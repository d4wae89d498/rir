#ifndef RIR_DEREF_H
# define RIR_DEREF_H
# include <rir.h>

static var *DeRef(value *v) {
    var *output = new(var, .var_type = V_STACK);

    return output;
}

# define deref(x) DeRef(x)

#endif // RIR_DEREF_H