#include <rir.h>

// === func ===
static int func_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        opt(tk("export")),
        id_rule,
        punc("("),
        opt(rep(id_rule)),
        punc(")"),
        stmt_rule
    ));
    if (match_size < 0)
        return -1;

    return match_size;
}
bpc_parser *func_parser = &func_parser_impl;