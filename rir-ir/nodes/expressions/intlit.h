#ifndef RIR_INTLIT_H
# define RIR_INTLIT_H
# include <rir.h>

struct  intlit {
    expr    expr;
    int     value;
};

visitable(node_visitor, node, intlit, self)

static intlit *intlit_new(int value) 
{
    return new(intlit, 
        .expr = expr_impl(
            .accept = &intlit_visit,
            .type = "intlit"
        ),
        .value = value
    );
}

# define intlit(X) value(&intlit_new(X)->expr)

#endif // RIR_INTLIT_H