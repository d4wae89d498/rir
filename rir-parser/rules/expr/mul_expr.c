#include <rir.h>

// === mul_expr ===
static int mul_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool eq = false;

    int match_size = apply(seq(
        unary_expr_rule,
        orep(seq(
            alt(tk("*"), tk("/"), tk("%")),
            unary_expr_rule
        ))
    ));
    if (match_size <= 0) {
        debug("not a mul!")
        return -1;
    }
    debug("got a mul!");
    return match_size;
}
bpc_parser *mul_expr_parser = &mul_expr_parser_impl;