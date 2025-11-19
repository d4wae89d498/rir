#include <rir.h>

// === add_expr ===
static int add_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        mul_expr_rule,
        orep(seq(
            alt(tk("+"), tk("-")),
            mul_expr_rule
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *add_expr_parser = &add_expr_parser_impl;