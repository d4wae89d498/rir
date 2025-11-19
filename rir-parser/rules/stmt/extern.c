#include <rir.h>

// === extern ===
static int extern_parser_impl(void *arg)
{
    TRACE;
    int match_size = apply(seq(
        punc("extern"),
        id_list_rule
    ));
    if (match_size < 0)
        return -1;

    return match_size;
}
bpc_parser *extern_parser = &extern_parser_impl;