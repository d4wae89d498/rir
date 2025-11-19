#include <rir.h>

// === arg_list ===
static int arg_list_parser_impl(void *arg)
{
    TRACE;
    (void) arg;

    // store stack sizes

    int match_size = apply(seq(
        expr_rule,
        orep(seq(alt(punc(","), expr_rule)))
    ));
    if (match_size < 0)
        return -1;

    // fpr each captured items..
    
    return match_size;
}
bpc_parser *arg_list_parser = &arg_list_parser_impl;