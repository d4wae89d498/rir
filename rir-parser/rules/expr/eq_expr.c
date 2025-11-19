#include <rir.h>

// === eq_expr ===
static int eq_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int eq = 0;

    int match_size = apply(seq(
        rel_expr_rule,
        orep(seq(
            alt(tk("!="), tk("==")),
            rel_expr_rule
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *eq_expr_parser = &eq_expr_parser_impl;