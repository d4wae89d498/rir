#ifndef RIR_LOAD_H
# define RIR_LOAD_H
# include <rir.h>

struct load {
    expr    expr;
    var     *v;
};

static void *load_visit(load *self, node_visitor *vis, void *ctx) {
    return 0;
}

static value *Load(var *v) 
{
    load *self = new(load, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &load_visit
            },
            .type = "store",
        }, 
        .v = v
    );
    return value(&self->expr);
}

# define load(v) Load(v)

#endif // RIR_LOAD_H