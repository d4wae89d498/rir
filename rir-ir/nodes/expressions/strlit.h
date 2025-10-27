#ifndef RIR_STRLIT_H
# define RIR_STRLIT_H
# include <rir.h>

struct strlit {
    expr        expr;
    const char  *value;
};

visitable(node_visitor, node, strlit, &self->expr.impl)

static value *StrLit(const char *str) {
    strlit *output = new(strlit,
        .expr = expr_impl(
            .accept = &strlit_visit,
            .type = "strlit"
        ),
        .value = str
    );
    return value(&output->expr);
}

# define strlit(v) StrLit(v)

#endif // RIR_STRLIT_H