#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

struct store {
    expr    expr;
    var     *dest;
    value   *v;
};

static void *store_visit(store *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "store").ref)->second(
        &self->expr.node,
        ctx
    );
}

static value *Store(var *dest, value *v) 
{
    store *self = new(store, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &store_visit
            },
            .type = "store", 
        },
        .dest = dest, 
        .v = v
    );
    return value(&self->expr);
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H