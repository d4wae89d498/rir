#ifndef RIR_UNARY_H
# define RIR_UNARY_H
# include "./../instr.h"
# include "./../value.h"

struct unaryop 
{
    expr        expr;
    const char  *type;
    value       *operand;
};


//     return hmap_find(visitor, "addw")(ctx);
# define def_unaryop(NAME)                                                  \
    static void * NAME ## _accept(void *visitor, void *ctx) {               \
        return 0;                                                           \
    }                                                                       \
                                                                            \
    static value * NAME(value *operand) {                                   \
        return value(&new(unaryop,                                          \
            .expr = {                                                       \
                .node = {                                                   \
                    .accept = (ir_node_method)&NAME ## _accept,             \
                },                                                          \
                .type = "unaryop"                                           \
            },                                                              \
            .type = #NAME ,                                                 \
            .operand = operand,                                             \
        )->expr);                                                           \
    }   


def_unaryop(not)
def_unaryop(inc)
def_unaryop(dec)
// operation for sign change ??

#endif // RIR_UNARY_H