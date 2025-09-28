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

static void *var_visit(var *self, node_visitor *vis, void *ctx) {
    return 0;
}

static var *Var(void) {
    static unsigned id;
    id += 1;
    var *out = new(var, 
        .instr = {
            .node = {
                .accept = (ir_node_method)&var_visit
            },
            .type = "var"
        },
        .id = id, 
        .type = V_REG
    );
    instr(&out->instr);
    return out;
}

# define var() Var()


#endif // RIR_VAR_H