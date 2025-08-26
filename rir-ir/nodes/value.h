#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include "expr.h"
# include "instr.h"

typedef struct value {
    instr_base

    int     id;
    expr    *e;
} value;


value *Value(expr *e) {
    instr_base

    value *out = new(value, 
        .e = e
    );
    return out;
}

# define value(v) Value(v)


#endif // RIR_VALUE_H