#include "diag.h"
#include <rir.h>

int main() {
    setup();
    fmt_println("=== testing print ===");

    // 1. build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *x1 = add2(intlit(2), intlit(4));
            ret(x1);
    builder_end();

    // 2. print it
    auto ctx = (print_target_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &ctx);
    fmt_println("-----\nGenerated IR:\n-");
    dump_file(stdout, ctx.ostream);
    fmt_println("-----");
    return 0;
}

