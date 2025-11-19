#include <rir.h>

// === expr ===
static int expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    return apply(cond_expr_rule);
}
bpc_parser *expr_parser = &expr_parser_impl;