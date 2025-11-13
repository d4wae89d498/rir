#include <rir.h>

// === id ===
static int id_parser_impl(void *arg)
{
    (void) arg;
    const char *start_ptr = std_parser_ctx->src;
    int match_size = apply(seq(
        alt(chris(isalpha), punc("_")),
        opt(rep(alt(chris(isalnum), punc("_"))))
    ));
    if (match_size <= 0)
        return -1;
    strstack_push(&std_parser_ctx->sstack,
        strndup(start_ptr, match_size)
    );
    return match_size;
}
bpc_parser *id_parser = &id_parser_impl;