#include <rir.h>

// === rel_expr ===
static int rel_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool eq = false;

    int expect_tk = true;
    int match_size = apply(seq(
        seq(add_expr_rule, setval(&expect_tk, false)),
        orep(seq(
            alt(tk(">"), tk("<"), tk("<="), tk(">=")),
            add_expr_rule
        ))
    ));
    if (match_size <= 0)
        return -1;

    if (!expect_tk)
        return match_size;
 

    if (!cstrstack_size(&csstack))
    {
        error("Unable to pull expr_parser_impl op!");
        return match_size;
    }

    const char *tk = cstrstack_pull(&csstack);
    
    if (tk[0] == '>') {
        if (tk[1] == '=') {
            
        }
    } else if (tk[0] == '<') {
        if (tk[1] == '=') {
            
        }
    }

    return match_size;
}
bpc_parser *rel_expr_parser = &rel_expr_parser_impl;