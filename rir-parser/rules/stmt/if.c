#include <rir.h>

// === if ===
static int if_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool has_else = false;

    int match_size = apply(seq(
        punc("if"),
        opt(punc("(")),
        expr_rule,
        opt(punc(")")),
        stmt_rule,
        opt(seq(punc("else"), stmt_rule, toggle(&has_else)))
    ));

    return match_size > 0 ? match_size : -1;
}
bpc_parser *if_parser = &if_parser_impl;