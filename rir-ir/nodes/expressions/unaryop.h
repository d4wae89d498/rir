#ifndef RIR_UNARY_H
# define RIR_UNARY_H
# include "./../instr.h"
# include "./../value.h"

typedef struct unaryop 
{
    expr_base
    const char  *unaryop_type;
    value       *operand;
} unaryop;


//     return hmap_find(visitor, "addw")(ctx);
# define def_unaryop(NAME)                                                  \
    static void * NAME ## _accept(void *visitor, void *ctx) {               \
        return 0;                                                           \
    }                                                                       \
                                                                            \
    static value * NAME(value *operand) {                                   \
        return new(unaryop,                                                 \
            .expr_type = "unaryop" ,                                        \
            .unaryop_type = #NAME ,                                         \
            .operand = operand,                                             \
        );                                                                  \
    }   

def_unaryop(not)
def_unaryop(inc)
def_unaryop(dec)
// operation for sign change ??

#endif // RIR_UNARY_H