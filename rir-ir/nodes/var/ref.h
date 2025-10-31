#ifndef RIR_REF_H
# define RIR_REF_H
# include <rir.h>

struct ref {
    expr    expr;
    var     *v;
};

visitable(node_visitor, node, ref, &self->expr.impl)

static ref *ref_new(var *v) {
    v->type = V_STACK;
    return new(ref, 
        .expr = expr_impl(
            .accept = &ref_visit,
            .type = "ref"
        ),
        .v = v
    );
}

static value *Ref(var *v) {
    ref *self = ref_new(v);
    return value(&self->expr);
}

# define ref(x) Ref(x)

#endif // RIR_REF_H