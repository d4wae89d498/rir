#include <rir.h>

// === stmt  ===
static int stmt_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool err;
    int match_size = apply(alt(
        stmt_block_rule,
        extern_rule,
        ret_rule,        
        if_rule,
        while_rule,
        for_rule,
        var_decl_rule,
        expr_rule,
        punc(";")
    ));

    if (match_size <= 0)
    {
        return -1;
//        return error_recovery("Unknown statement '%s'");
    }
    int v;
    switch(v) {
        case 0:
            if (0) {
                break;
            };
            
    }

    return match_size > 0 ? match_size : -1;
}
bpc_parser *stmt_parser = &stmt_parser_impl;

