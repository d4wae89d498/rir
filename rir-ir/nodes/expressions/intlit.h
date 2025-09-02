#ifndef RIR_INTLIT_H
# define RIR_INTLIT_H
# include <rir.h>

struct intlit
{
    expr    expr;
    int     value;
};

static void *intlit_visit(intlit *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "intlit").ref)->second(
        &self->expr.node,
        ctx
    );
}

static value *IntLit(int value) 
{
    intlit *e = new(intlit, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &intlit_visit
            },
            .type = "intlit"
        },
        .value = value
    );
    return value(&e->expr);
}

#endif // RIR_INTLIT_H