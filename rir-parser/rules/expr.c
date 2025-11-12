#include <rir.h>

// === expr ===
static int expr_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(cond_expr_rule);
    return match_size > 0 ? match_size : -1;
}
bpc_parser *expr_parser = &expr_parser_impl;