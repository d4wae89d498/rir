#include <rir.h>


// === unary_expr ===
static int unary_expr_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    bool eq = false;
    bool expect_tk = false;

    int match_size = apply(alt(
        postfix_expr_rule,
        seq(alt(
                seq(tk("++"), unary_expr_rule),
                seq(tk("--"), unary_expr_rule),
                seq(tk("&"), id_rule),
                seq(alt(tk("*"), tk("+"), tk("-"), tk("!")), unary_expr_rule)
            ),
            toggle(&expect_tk)
        )
    ));

    if (match_size <= 0)
        return -1;

    if (!expect_tk)
        return match_size;

    if (!cstrstack_size(&csstack))
    {
        error("Unable to find unary op");
        exit(1);
        return match_size;
    }
    const char *tk = cstrstack_pull(&csstack);
    if (!strcmp(tk, "++")) {

    } else if (!strcmp(tk, "--")) {

    } else switch (tk[0]) {
        
    case '&':
        break;

    case '*':
        break;

    case '-':
        break;

    case '!':
        break;

    default:
        error("Unknown token [%s] in unary_expr", tk);
        exit(1);
    }
    
    return match_size;
}
bpc_parser *unary_expr_parser = &unary_expr_parser_impl;