#include <rir.h>

// === for ===
static int for_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("for"),
        tk("("),
        opt(rule(assign_parser)),
        tk(";"),
        opt(rule(expr_parser)),
        tk(";"),
        opt(rule(assign_parser)),
        tk(")"),
        rule(stmt_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *for_parser = &for_parser_impl;