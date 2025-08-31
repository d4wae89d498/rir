#ifndef RIR_VAR_H
# define RIR_VAR_H
# include <rir.h>

struct var {
    const char  *name;
    enum var_type {
                V_REG,      //  Default
                V_STACK,    //  Created by ref(var), ref will returns a value and promote var to V_STACK
                V_PTR       //  Created by var = deref(value), deref returns a V_PTR var
    }           var_type;
};

static var *Var(const char *name) {
    var *out = new(var, .name = name, .var_type = V_REG);
    return out;
}

# define var(n) Var(n)


#endif // RIR_VAR_H