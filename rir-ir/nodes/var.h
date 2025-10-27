#ifndef RIR_VAR_H
# define RIR_VAR_H
# include <rir.h>

struct var {
    instr       instr;
    unsigned    id;
    enum var_type {
                V_REG,      //  Default
                V_STACK,    //  Created by ref(var), ref will returns a value and promote var to V_STACK
                V_PTR       //  Created by var = deref(value), deref returns a V_PTR var
    }           type;
};

visitable(node_visitor, node, var, &self->instr.impl)

static var *Var(void) {
    static unsigned id;

    var *out = new(var, 
        .instr = instr_impl(
            .accept = &var_visit, 
            .type = "var"
        ),
        .id = id++, 
        .type = V_REG
    );
    builder_attach_instr(&out->instr);
    return out;
}

# define var() Var()


#endif // RIR_VAR_H