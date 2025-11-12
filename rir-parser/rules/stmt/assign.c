#include <rir.h>

// === assign  ===
static int assign_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        unary_expr_rule,
        tk("="),
        expr_rule
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *assign_parser = &assign_parser_impl;


