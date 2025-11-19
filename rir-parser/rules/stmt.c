#include <rir.h>

// === stmt  ===
static int stmt_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool err;
    int match_size = apply(alt(
        extern_rule,
        ret_rule,
        expr_rule,
        stmt_block_rule,
        if_rule,
        while_rule,
        for_rule,
        punc(";")
    ));

    if (match_size <= 0)
    {
        return error_recovery("Unknown statement '%s'");
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

