#include <rir.h>

// === prog ===
static int prog_parser_impl(void *arg)
{
    (void) arg;
    prog *prog = prog();
    int match_size = apply(
        rep(rule(func_parser))
    );
    if (match_size >= 0) {
      //  std_parser_ctx
    }
    return match_size > 0 ? match_size : -1;
}
bpc_parser *prog_parser = &prog_parser_impl;