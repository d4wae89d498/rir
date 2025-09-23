#ifndef RIR_RESOLVE_H
# define RIR_RESOLVE_H
# include <rir.h>

typedef struct resolve {
    expr        expr;
    prog        *prog;
    const char  *symbol_name;
} resolve;

static void *resolve_visit(arg *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "resolve").ref)->second(
        &self->expr.node,
        ctx
    );
}

value *Resolve(const char *symbol_name) {
    resolve *self = new(resolve, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &resolve_visit
            },
            .type = "resolve"
        },
        .symbol_name = symbol_name
    );
    return value(&self->expr);
}

# define resolve(name) Resolve(name)

#endif // RIR_RESOLVE_H