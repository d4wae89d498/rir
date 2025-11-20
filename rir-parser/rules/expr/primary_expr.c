#include <rir.h>

// === primary_expr ===
static int primary_expr_impl(void *arg)
{
    TRACE;
    (void) arg;

    enum {
        lit,
        id,
        expr
    } match_type;

    int match_size = apply(alt(
        seq(intlit_rule, setval((int*)&match_type, lit)),
        seq(strlit_rule, setval((int*)&match_type, lit)),
        seq(id_rule, setval((int*)&match_type, id)),
        seq(tk("("), expr_rule, tk(")"), setval((int*)&match_type, expr))
    ));
    if (match_size <= 0)
        return -1;

    switch (match_type) {
        case lit:
            break;
        case id:
            debug("ID ACCEPTED (%d) '%.2s'", match_size, std_parser_ctx->src - 2)
            // emits a value* ? like resolve("..") ?
            // but then & value ?
            // resolved later.. ?
 
            break;
        case expr:
            break;
        default:
            error("Unknown match_type %d in primary_expr ", match_type);
            exit(1);
    }

    return match_size;
}
bpc_parser *primary_expr_parser = &primary_expr_impl;
