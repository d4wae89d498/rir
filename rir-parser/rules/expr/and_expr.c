#include <rir.h>

// === and_expr ===
static int and_expr_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        eq_expr_rule,
        opt(rep(seq(
            tk("&&"),
            eq_expr_rule
        )))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *and_expr_parser = &and_expr_parser_impl;