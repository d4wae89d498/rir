#include <rir.h>

// === top_decl  ===
static int top_decl_impl(void *arg)
{
    TRACE;
    (void) arg;
    int match_size = apply(alt(
        func_rule,
        seq(var_decl_rule, punc(";")),
        seq(extern_rule, punc(";")),
        punc(";")
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *top_decl_parser = &top_decl_impl;

