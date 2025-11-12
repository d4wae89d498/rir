#include <rir.h>

// === id ===
static int id_parser_impl(void *arg)
{
    (void) arg;
    const char *start_ptr = std_parser_ctx->src;
    int match_size = apply(seq(
        alt(chris(isalpha), tk("_")),
        opt(rep(alt(chris(isalnum), tk("_"))))
    ));
    if (match_size <= 0)
        return -1;
  //  strstack_push(&std_parser_ctx->stack, strndup(start_ptr, match_size));
    pnode_stack_push(&std_parser_ctx->pnstack, &htoken_new( 
        strndup(start_ptr, match_size)
    )->base);
    return match_size;
}
bpc_parser *id_parser = &id_parser_impl;