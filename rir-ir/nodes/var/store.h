#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

struct store {
    instr    instr;
    var     *dest;
    value   *v;
};

static void *store_visit(store *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "store").ref)->second(
        &self->instr.node,
        ctx
    );
}

static void Store(var *dest, value *v) 
{
    store *self = new(store, 
        .instr = {
            .node = {
                .accept = (ir_node_method) &store_visit,
                .type = "instr"
            },
            .type = "store", 
        },
        .dest = dest, 
        .v = v
    );
    builder_attach_instr(&self->instr);    

    return;
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H