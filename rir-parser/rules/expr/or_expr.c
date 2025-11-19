#include <rir.h>

// === or_expr ===
static int or_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        and_expr_rule,
        orep(seq(
            tk("||"),
            and_expr_rule
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *or_expr_parser = &or_expr_parser_impl;