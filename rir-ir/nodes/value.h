#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include <rir.h>
#include <stdio.h>

struct value {
    instr   instr;
    int     id;
    expr    *e;
};

static void *value_visit(value *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis, "value").ref)->second(
        &self->instr.node, 
        ctx
    );
}

# define value(v) Value(v)
static value *Value(expr *e) {

    static int nb;

    nb++;

 
    value *out = new(value, 
        .instr = {
            .node = {
                .accept = (ir_node_method) &value_visit,
                .type = "instr"
            },
            .type = "value",
            .prev = 0,
            .next = 0,
        },
        .id = nb,
        .e = e,
    );

    printf("attachin..\n");
    builder_attach_instr(&out->instr);
    printf("attached.\n");
    return out;
}

#endif // RIR_VALUE_H