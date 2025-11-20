#include <rir.h>

// === assign  ===

#define ASSIGNEMENT_TOKENS \
    punc("="),\
    punc("+="),\
    punc("-="),\
    punc("*="),\
    punc("/="),\
    punc("%=")

static int assign_parser_impl(void *arg)
{
    TRACE;
    (void) arg;

    int match_size = apply(alt(
        seq(unary_expr_rule, alt(ASSIGNEMENT_TOKENS), assign_rule),
        cond_expr_rule
    ));

    if (match_size <= 0)
        return -1;
    debug("got assign of size=%d!\n\n\n", match_size)
    return match_size;
}
bpc_parser *assign_parser = &assign_parser_impl;


