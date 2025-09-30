#include <rir.h>

int main() {
    fmt_println("==== testing vars ====");
    // Build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            block("b1");
                value *x1 = add(intlit(2), intlit(4));
                var *v1 = var();

                store(v1, x1);

                call(resolve("printf"), strlit("hello %d"), intlit(2));
                ret(x1);
    builder_end();

    // Print it
    setup_targets();
    auto e = Targets_find(&targets, "print").ref;
    if (!e) {
        fmt_printd(stderr, "ERROR, print target not found.\n");
        exit(1);
    }
    auto vis = e->second->vis;
    dot(demo->node, accept, vis, 0);
    fmt_println("Exiting... {}\n", (void*)vis);
    
    return 0;
}

