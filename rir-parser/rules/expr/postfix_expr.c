#include <rir.h>

// === postfix_expr ===
static int postfix_expr_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(primary_expr_rule, opt(rep(postfix_suffix_rule))));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *postfix_expr_parser = &postfix_expr_impl;

// === postfix_suffix ===
static int postfix_suffix_impl(void *arg)
{
    (void) arg;
    int match_size = apply(alt(
        seq(tk("["), expr_rule, tk("]")),
        seq(tk("("), expr_rule, tk(")")),
        tk("++"),
        tk("--")
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *postfix_suffix_parser = &postfix_suffix_impl;