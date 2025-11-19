#include <rir.h>

// === prog ===
static int prog_parser_impl(void *arg)
{
    TRACE;
    (void) arg;
    debug("parsing prog...")
    prog *prog = prog();
    int match_size = apply(
        rep(func_rule)
    );
    if (match_size <= 0) {
        return -1;
    }
    return match_size;
}
bpc_parser *prog_parser = &prog_parser_impl;