#include <rir.h>

// === label ===
static int label_parser_impl(void *arg)
{
    TRACE;
    (void) arg;

    int match_size = apply(seq(
        id_rule,
        punc(":")
    ));

    if(match_size <= 0)
        return -1;

    return match_size;
}
bpc_parser *label_parser = &label_parser_impl;