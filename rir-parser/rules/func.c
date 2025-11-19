#include <rir.h>

// === func ===
static int func_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    debug("parsing func...")
    int match_size = apply(seq(
        opt(tk("export")),
        id_rule,
        punc("("),
        id_list_rule,
        punc(")"),
        stmt_rule
    ));
    notice("parsing func done %d", match_size);
    if (match_size < 0)
        return -1;
    debug("func size: %d [%.*s]", match_size, match_size, std_parser_ctx->src - match_size)
    return match_size;
}
bpc_parser *func_parser = &func_parser_impl;