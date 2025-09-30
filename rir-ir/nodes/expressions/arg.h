#ifndef RIR_ARG_H
# define RIR_ARG_H
# include <rir.h>

struct arg
{
    expr        expr;
    unsigned    n;
};

static void *arg_visit(arg *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "arg").ref)->second(
        &self->expr.node,
        ctx
    );
}

static value *Arg(unsigned n) {
    expr *self = &(new(arg, 
        .expr = (expr){
            .type = "arg",
            .node = {
                .accept = (ir_node_method) &arg_visit
            }
        },
        .n = n
    ))->expr;
    return value(self);
}

# define arg(n) Arg(n)

#endif // RIR_ARG_H