#include <rir.h>


// === unary_expr ===
static int unary_expr_parser_impl(void *arg)
{
    (void) arg;
    bool eq = false;

    int match_size = apply(alt(
        postfix_expr_rule,
        seq(tk("++"), unary_expr_rule),
        seq(tk("--"), unary_expr_rule),
        seq(alt(tk("&"), tk("*"), tk("+"), tk("-"), tk("!")), unary_expr_rule)
    ));
    
    return match_size > 0 ? match_size : -1;
}
bpc_parser *unary_expr_parser = &unary_expr_parser_impl;