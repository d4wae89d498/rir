#include <rir.h>

# define MAX_INT_LEN 20
# define min(a, b) (a < b) ? a : b

// === intlit ===
static int intlit_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    const char *start_ptr = std_parser_ctx->src;
    int match_size = apply(rep(chris(isdigit)));
    if (match_size <= 0)
        return -1;

    char buffer[MAX_INT_LEN + 1];
    strncpy(buffer, start_ptr, min(match_size, MAX_INT_LEN));

    value *pushme = value_new(temp_id++, &intlit_new(
        atoi(buffer)
    )->expr);

    nodestack_push(&nstack, &pushme->instr.node);

    return match_size;
}
bpc_parser *intlit_parser = &intlit_parser_impl;

