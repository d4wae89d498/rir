#ifndef RIR_STRLIT_H
# define RIR_STRLIT_H
# include <rir.h>

struct  strlit {
    expr        expr;
    const char  *value;
};

visitable(node_visitor, node, strlit, self)

static strlit *strlit_new(const char *str) {
    return new(strlit,
        .expr = expr_impl(
            .accept = &strlit_visit,
            .type = "strlit"
        ),
        .value = str
    );
}

# define strlit(v) value(&(strlit_new(v)->expr))

#endif // RIR_STRLIT_H