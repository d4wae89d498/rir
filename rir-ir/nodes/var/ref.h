#ifndef RIR_REF_H
# define RIR_REF_H
# include <rir.h>

struct ref {
    expr    expr;
    var     *v;
};

static void *ref_visit(ref *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "load").ref)->second(
        &self->expr.node,
        ctx
    );
}

static value *Ref(var *v) {
    v->type = V_STACK;
    ref *self = new(ref, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &ref_visit,
                .type = "instr"
            },
            .type = "ref"
        },
        .v = v
    );
    return value(&self->expr);
}

# define ref(x) Ref(x)

#endif // RIR_REF_H