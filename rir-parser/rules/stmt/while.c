#include <rir.h>

// === while ===
static int while_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("while"),
        tk("("),
        rule(expr_parser),
        tk(")"),
        rule(stmt_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *while_parser = &while_parser_impl;