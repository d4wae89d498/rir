#include <rir.h>

int main() {
    // Build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *x1 = add2(intlit(2), intlit(4));
            ret(x1);
    builder_end();

    // Print it
    setup();
    auto e = Targets_find(&targets, "print").ref;
    if (!e) {
        fmt_printd(stderr, "ERROR, print target not found.\n");
        exit(1);
    }
    auto visitor = e->second->visitor;
    auto ctx = (print_target_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, visitor, &ctx);

    fmt_println("-----\nGenerated IR:\n-");
    dump_file(stdout, ctx.ostream);
    fmt_println("-----");
    fmt_println("Exiting... {}\n", (void*)visitor);
    return 0;
}

