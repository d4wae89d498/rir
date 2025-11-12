#include <rir.h>

// === add_expr ===
static int add_expr_parser_impl(void *arg)
{
    (void) arg;
    bool eq = false;

    int match_size = apply(seq(
        mul_expr_rule,
        opt(rep(seq(
            alt(tk("+"), tk("-")),
            mul_expr_rule
        )))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *add_expr_parser = &add_expr_parser_impl;