#include <rir.h>

// === mul_expr ===
static int mul_expr_parser_impl(void *arg)
{
    (void) arg;
    bool eq = false;

    int match_size = apply(seq(
        unary_expr_rule,
        opt(rep(seq(
            alt(tk("*"), tk("/"), tk("%")),
            unary_expr_rule
        )))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *mul_expr_parser = &mul_expr_parser_impl;