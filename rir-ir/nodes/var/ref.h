#ifndef RIR_REF_H
# define RIR_REF_H
# include <rir.h>

struct ref {
    node    node;
    expr    expr;
    var     *v;
};

static void *ref_visit(store *self, node_visitor *vis, void *ctx) {
    return 0;
}

static value *Ref(var *v) {
    // todo:: store ref into CFG block
    v->type = V_STACK;
    ref *self = new(ref, 
        .node = {
            .accept = (ir_node_method) &ref_visit
        },
        .v = v
    );
    return value(&self->expr);
}

# define ref(x) Ref(x)

#endif // RIR_REF_H