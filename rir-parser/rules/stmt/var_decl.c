#include <rir.h>

// === var_decl ===
static int var_decl_impl(void *arg)
{
    TRACE;
    (void) arg;
    
    int match_size = apply(seq(
        opt(punc("static")),
        alt(
            seq(punc("var"), id_rule, opt(seq(punc("="), assign_rule))),
            seq(punc("const"), id_rule, punc("="), assign_rule)
        )
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *var_decl_parser = &var_decl_impl;
