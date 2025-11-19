# include <rir.h>

// === id_list ===
static int id_list_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(seq(
        id_rule,
        orep(seq(punc(","), id_rule))
    ));
    if (match_size < 0)
        return -1;

    return match_size;
}
bpc_parser *id_list_parser = &id_list_impl;