#include <rir.h>

// === func ===
static int func_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        opt(tk("export")),
        rule(id_parser),
        tk("("),
        opt(rep(rule(id_parser))),
        tk(")"),
        rule(stmt_block_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *func_parser = &func_parser_impl;