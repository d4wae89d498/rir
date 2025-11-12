#include <rir.h>

// === intlit ===
static int intlit_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    const char *start_ptr = std_parser_ctx->src;
    int match_size = apply(rep(chris(isdigit)));
    if (match_size <= 0)
        return -1;
    const char *str = strndup(start_ptr, match_size);

    value *pushme = value_new(temp_id++, &intlit_new(
        atoi(str)
    )->expr);

    // todo: pushme

    free((void*)str);

    return match_size;
}
bpc_parser *intlit_parser = &intlit_parser_impl;

