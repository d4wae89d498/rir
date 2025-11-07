#ifndef RIR_EXPR_H
# define RIR_EXPR_H
# include <rir.h>

struct  expr {
    node        node;
    node        impl;
};

visitable(node_visitor, node, expr, self)

static expr ExprImpl(node impl) {
    return (expr) {
        .node = {
            .accept = &expr_visit,
            .type = "expr"
        },
        .impl = impl
    };
}

# define expr_impl(...) ExprImpl((node){__VA_ARGS__})

#endif // RIR_EXPR_H