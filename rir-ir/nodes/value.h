#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include <rir.h>

struct value {
    instr   instr;
    int     id;
    expr    *e;
};

visitable(node_visitor, node, value, &self->instr.impl)

static value *Value(expr *e) {
    static int nb;

    value *out = new(value, 
        .instr = instr_impl(
            .accept = &value_visit, 
            .type = "value"
        ),
        .id = nb++,
        .e = e
    );
    builder_attach_instr(&out->instr);
    return out;
}

# define value(e) Value(e)

#endif // RIR_VALUE_H