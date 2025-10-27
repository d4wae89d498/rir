#ifndef RIR_DEREF_H
# define RIR_DEREF_H
# include <rir.h>

struct deref {
    instr   instr;
    value   *v;
    var     *dest;
};

visitable(node_visitor, node, deref, &self->instr.impl)

// todo:: make it better... if __new suffix, maybe use an helper func?
static var *deref_new(value *val) {
    var *out = var();
    out->type = V_PTR;
    deref *self = new(deref,         
        .instr = instr_impl(
            .accept = &deref_visit,
            .type = "deref" 
        ),
        .v = val,
        .dest = out
    );
    builder_attach_instr(&self->instr);    
    return out;
}

# define deref(x) deref_new(x)

#endif // RIR_DEREF_H