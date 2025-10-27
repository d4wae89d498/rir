#ifndef RIR_RESOLVE_H
# define RIR_RESOLVE_H
# include <rir.h>

struct resolve {
    expr        expr;
    const char  *symbol_name;
};

visitable(node_visitor, node, resolve, &self->expr.impl)

static resolve *resolve_new(const char *symbol_name) {
    return new(resolve, 
        .expr = expr_impl(
            .accept = &resolve_visit,
            .type = "resolve"
        ),
        .symbol_name = symbol_name
    );
}

# define resolve(name) value(&resolve_new(name)->expr)

#endif // RIR_RESOLVE_H