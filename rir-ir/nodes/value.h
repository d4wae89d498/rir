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
    instr *out = new(value, 
        .e = e,
        .prev = 0,
        .next = 0
    );
    block *b = builder_get_block();
    // todo if no b... error
    if (!b->start)
    {
        b->start = b->last =  out;
    }
    else
    {
        out->prev = b->last;
        b->last = out;
    }
    return (value*)out;
}

# define value(v) Value(v)


#endif // RIR_VALUE_H