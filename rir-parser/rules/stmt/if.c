#include <rir.h>

// === if ===
static int if_parser_impl(void *arg)
{
    (void) arg;
    bool has_else = false;

    int match_size = apply(seq(
        punc("if"),
        punc("("),
        expr_rule,
        punc(")"),
        stmt_rule,
        opt(seq(punc("else"), stmt_rule, toggle(&has_else)))
    ));

    return match_size > 0 ? match_size : -1;
}
bpc_parser *if_parser = &if_parser_impl;