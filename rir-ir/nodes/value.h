#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include <rir.h>

struct value {
    instr   instr;
    int     id;
    expr    *e;
};

static void *value_visit(value *self, node_visitor *vis, void *ctx) {
    trace();
    return (node_visitor_find(vis, "value").ref)->second(
        &self->instr.node, 
        ctx
    );
}

static value *Value(expr *e) {
#   define value(v) Value(v)

    static int nb;

    nb++;

 
    value *out = new(value, 
        .instr = {
            .node = {
                .accept = (ir_node_method) &value_visit
            },
            .prev = 0,
            .next = 0,
        },
        .id = nb,
        .e = e,
    );
    
    instr(&out->instr);
   
    return out;
}

#endif // RIR_VALUE_H