#ifndef RIR_DEREF_H
# define RIR_DEREF_H
# include <rir.h>

struct deref {
    node    node;
    value   *v;
    var     *dest;
};

static void *deref_visit(deref *self, node_visitor *vis, void *ctx) {
    return 0;
}

static var *DeRef(value *v) {
    // todo:: store deref into CFG block
    var *out = var(v);
    out->type = V_PTR;
    return out;
}

# define deref(x) DeRef(x)

#endif // RIR_DEREF_H