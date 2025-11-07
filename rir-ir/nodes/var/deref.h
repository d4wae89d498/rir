#ifndef RIR_DEREF_H
# define RIR_DEREF_H
# include <rir.h>

struct  deref {
    instr   instr;
    value   *v;
    var     *dest;
};

visitable(node_visitor, node, deref, self)

static deref *deref_new(var *dest, value *val) {
    dest->type = V_PTR; // todo:: check if type was not changed from ptr to sometthing else ? or let it silent as is..
    return new(deref,         
        .instr = instr_impl(
            .accept = &deref_visit,
            .type = "deref" 
        ),
        .v = val,
        .dest = dest
    );
}

static var *Deref(value *x) {
    deref *self = deref_new(var(), x);
    builder_attach_instr(&self->instr);
    return self->dest;
}

# define deref(x) Deref(x)

#endif // RIR_DEREF_H