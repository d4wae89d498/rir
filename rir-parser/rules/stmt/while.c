#include <rir.h>

// === while ===
static int while_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        punc("while"),
        opt(punc("(")),
        expr_rule,
        opt(punc(")")),
        stmt_rule
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *while_parser = &while_parser_impl;