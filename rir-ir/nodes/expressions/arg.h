#ifndef RIR_ARG_H
# define RIR_ARG_H
# include <rir.h>

struct  arg
{
    expr        expr;
    unsigned    n;
};

visitable(node_visitor, node, arg, self)

static arg *arg_new(unsigned n) {
    return new(arg, 
        .expr = expr_impl(
            .accept = &arg_visit,
            .type = "arg",
        ),
        .n = n
    );
}

# define arg(n) value(&arg_new(n)->expr)

#endif // RIR_ARG_H