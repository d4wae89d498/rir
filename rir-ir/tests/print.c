#include <rir.h>

int main() {
    setup();
    notice("=== testing print ===");

    // 1. build the IR
    prog *demo = prog();
    function("main");
        value *x1 = add2(intlit(2), intlit(4));
        ret(x1);

    // 2. print it
    auto ctx = (print_visitor_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &ctx);
    notice("-----\nGenerated IR:\n-");
    dump_file(stdout, ctx.ostream);
    notice("-----");
    return 0;
}

