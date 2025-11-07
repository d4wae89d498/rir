#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include <rir.h>

struct __attribute__((packed)) value {
    instr   instr;
    int     id;
    expr    *e;
};

visitable(node_visitor, node, value, self)

static value *value_new(int id, expr *e) {
    return new(value, 
        .instr = instr_impl(
            .accept = &value_visit, 
            .type = "value"
        ),
        .id = id,
        .e = e
    );
}

static value *Value(expr *e) {
    static int id;

    value *out = value_new(id++, e);
    builder_attach_instr(&out->instr);
    return out;
}

# define value(e) Value(e)

#endif // RIR_VALUE_H