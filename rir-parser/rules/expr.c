#include <rir.h>

// === expr ===
static int expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    return apply(seq(assign_rule, orep(seq(tk(","), assign_rule))));
}
bpc_parser *expr_parser = &expr_parser_impl;