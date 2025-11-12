#include <rir.h>

// === if ===
static int if_parser_impl(void *arg)
{
    (void) arg;
    bool has_else = false;

    int match_size = apply(seq(
        tk("if"),
        tk("("),
        rule(expr_parser),
        tk(")"),
        rule(stmt_parser),
        opt(seq(tk("else"), rule(stmt_parser), toggle(&has_else)))
    ));

    return match_size > 0 ? match_size : -1;
}
bpc_parser *if_parser = &if_parser_impl;