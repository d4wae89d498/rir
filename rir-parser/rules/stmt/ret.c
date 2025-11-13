#include <rir.h>

// === ret ===
static int ret_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        punc("return"),
        opt(expr_rule)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *ret_parser = &ret_parser_impl;
