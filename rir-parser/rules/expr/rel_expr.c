#include <rir.h>

// === rel_expr ===
static int rel_expr_parser_impl(void *arg)
{
    (void) arg;
    bool eq = false;

    int match_size = apply(seq(
        add_expr_rule,
        orep(seq(
            alt(tk(">"), tk("<"), tk("<="), tk(">=")),
            add_expr_rule
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *rel_expr_parser = &rel_expr_parser_impl;