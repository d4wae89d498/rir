#include <rir.h>

// === cond_expr ===
static int cond_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        or_expr_rule,
        opt(seq(
            punc("?"),
            expr_rule,
            punc(":"),
            cond_expr_rule
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *cond_expr_parser = &cond_expr_parser_impl;