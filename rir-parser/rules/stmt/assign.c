#include <rir.h>


// === assign  ===
static int assign_parser_impl(void *arg)
{
    TRACE;
    (void) arg;

    bool is_const = false;
    int match_size = apply(seq(
        seq(punc("const"), toggle(&is_const)),
        unary_expr_rule,
        punc("="),
        expr_rule
    ));
    if (match_size <= 0)
        return -1;

    int y;
    int i[(y = 4)];

    if (is_const) {
        // push to a label/value table
    } else {
        // pop node once => we have an expr 
        // pop node again => check return type -- shall be a var* => else error (trying to assign to an lvalue...)
        // Store(var *dest, value *v)

        //    *(ptr) ==> ret a var*
        //    *&*&ptr + 4
    }

    // maybe make *ptr deref operation returns a value* AND a var*
    // depending on context, when & or on left side=>we woulduse var*  elsethevalue

    return match_size;
}
bpc_parser *assign_parser = &assign_parser_impl;


