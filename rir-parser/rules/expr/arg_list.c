#include <rir.h>

// === arg_list ===
static int arg_list_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        expr_rule,
        opt(rep(seq(alt(tk(","), expr_rule)))))
    );
    return match_size > 0 ? match_size : -1;
}
bpc_parser *arg_list_parser = &arg_list_parser_impl;