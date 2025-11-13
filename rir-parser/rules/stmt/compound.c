#include <rir.h>

// === stmt_block ===
static int stmt_block_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        punc("{"),
        rep(stmt_rule),
        punc("}")
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *stmt_block_parser = &stmt_block_parser_impl;