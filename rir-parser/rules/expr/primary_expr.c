#include <rir.h>

// === primary_expr ===
static int primary_expr_impl(void *arg)
{
    (void) arg;
    int match_size = apply(alt(
        intlit_rule,
        strlit_rule,
        id_rule,
        seq(tk("("), expr_rule, tk(")"))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *primary_expr_parser = &primary_expr_impl;
