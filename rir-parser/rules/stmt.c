#include <rir.h>

// === stmt  ===
static int stmt_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(alt(
        assign_rule,
        expr_rule,
        stmt_block_rule,
        if_rule,
        while_rule,
        for_rule,
        punc(";")
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *stmt_parser = &stmt_parser_impl;

