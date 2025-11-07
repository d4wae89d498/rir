#ifndef RIR_UNARY_H
# define RIR_UNARY_H
# include <rir.h>

struct  unaryop {
    expr        expr;
    const char  *type;
    value       *operand;
};

visitable(node_visitor, node, unaryop, self)

# define def_unaryop(NAME)                                                  \
    static unaryop * NAME ## 1 ## _new (value *operand) {                   \
        return new(unaryop,                                                 \
            .expr = expr_impl(                                              \
                .accept = &unaryop_visit,                                   \
                .type = "unaryop"                                           \
            ),                                                              \
            .type = #NAME ,                                                 \
            .operand = operand                                              \
        );                                                                  \
    }                                                                       \
    static value * NAME ## 1 (value *operand) {                             \
        return value(& NAME ## 1 ## _new (operand)->expr);                          \
    }

def_unaryop(not)
def_unaryop(inc)
def_unaryop(dec)

#endif // RIR_UNARY_H