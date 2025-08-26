#ifndef RIR_BINOP_H
# define RIR_BINOP_H
# include "./../expr.h"
# include "./../value.h"

typedef struct binop 
{
    expr_base
    const char *binop_type;
    value *left;
    value *right;
} binop;


//     return hmap_find(visitor, "addw")(ctx);
# define def_binop(NAME)                                                \
    static void * NAME ## _accept(void *visitor, void *ctx) {           \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    static value * NAME(value *left, value *right) {                    \
        return 0;                                                       \
    }

/*
 return new(binop,                                               \
            .expr_type = "binop",                                       \
            .binop_type = #NAME,                                        \
            .left = left,                                               \
            .right = right                                              \
        );                                                              \

*/


def_binop(add)   // both operands signed or unsigned, same bitwise op, addition
def_binop(sub)   // both operands signed or unsigned, same bitwise op, subtraction
def_binop(mul)   // both operands unsigned, unsigned multiplication
//def_binop(div)   // both operands unsigned, unsigned division
def_binop(mod)   // both operands unsigned, unsigned remainder

def_binop(imul)  // both operands signed, signed multiplication (two’s complement)
def_binop(idiv)  // both operands signed, signed division
def_binop(imod)  // both operands signed, signed remainder

def_binop(and)   // bitwise AND, operands treated as bits
def_binop(or)    // bitwise OR, operands treated as bits
def_binop(xor)   // bitwise XOR, operands treated as bits
def_binop(shl)   // shift left logical, unsigned shift
def_binop(shr)   // shift right logical, unsigned shift (zero fill)
def_binop(ashr)  // arithmetic shift right, signed shift (sign-extend)

def_binop(eq)    // equality comparison, returns boolean (0 or 1)
def_binop(ne)    // inequality comparison, returns boolean
def_binop(ult)   // unsigned less than, boolean result
def_binop(ule)   // unsigned less or equal, boolean result
def_binop(ugt)   // unsigned greater than, boolean result
def_binop(uge)   // unsigned greater or equal, boolean result
def_binop(slt)   // signed less than, boolean result
def_binop(sle)   // signed less or equal, boolean result
def_binop(sgt)   // signed greater than, boolean result
def_binop(sge)   // signed greater or equal, boolean result



#endif // RIR_BINOP_H