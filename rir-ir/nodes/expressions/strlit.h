#ifndef RIR_STRLIT_H
# define RIR_STRLIT_H
# include <rir.h>

struct strlit
{
    expr        expr;
    const char  *value;
};

static void *strlit_visit(strlit *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "strlit").ref)->second(
        &self->expr.node,
        ctx
    );
}

static value *StrLit(const char *str) {
    printf("hmm/..\n");
    strlit *self = new(strlit,
        .expr = {
            .node = {
                .accept = (ir_node_method) &strlit_visit,
                .type = "expr"
            },
            .type = "strlit"
        },
        .value = str
    );
    printf("??\n");
    value* val = value(&self->expr);
    printf("end...\n");
    return val;
}

# define strlit(v) StrLit(v)

#endif // RIR_STRLIT_H