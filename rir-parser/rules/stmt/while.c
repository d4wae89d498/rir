#include <rir.h>

// === while ===
static int while_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        punc("while"),
        punc("("),
        expr_rule,
        punc(")"),
        stmt_rule
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *while_parser = &while_parser_impl;