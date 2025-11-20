#include <rir.h>

// === for ===
static int for_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool has_assign = false;
    bool has_cond = false;
    bool has_incr = false;

    int match_size = apply(seq(
        punc("for"),
        opt(punc("(")),
        opt(seq(assign_rule, toggle(&has_assign))),
        punc(";"),
        opt(seq(expr_rule, toggle(&has_cond))),
        punc(";"),
        opt(seq(assign_rule, toggle(&has_incr))),
        opt(punc(")")),
        stmt_rule
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *for_parser = &for_parser_impl;