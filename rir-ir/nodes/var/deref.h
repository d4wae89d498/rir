#ifndef RIR_DEREF_H
# define RIR_DEREF_H
# include <rir.h>

struct deref {
    instr   instr;
    value   *v;
    var     *dest;
};

static void *deref_visit(deref *self, node_visitor *vis, void *ctx) {
    return 0;
}

static var *DeRef(value *val) {
    var *out = var(val);

    deref *self = new(deref, 
        .instr = {
            .node = {
                .accept = (ir_node_method) &deref_visit
            },
            .type = "deref"
        },
        .v = val,
        .dest = out
    );
    instr(&self->instr);

    out->type = V_PTR;
    return out;
}

# define deref(x) DeRef(x)

#endif // RIR_DEREF_H