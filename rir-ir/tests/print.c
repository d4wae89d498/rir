#include <rir.h>
#include <stdio.h>

int main() {
    // Build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            block("b1");
                value *x1 = add(intlit(2), intlit(4));
                ret(x1);
    builder_end();

    // Print it
    trace();
    setup_targets();
    auto e = Targets_find(&targets, "print").ref;
    if (!e) {
        fprintf(stderr, "ERROR, print target not found.");
        exit(1);
    }
    auto vis = e->second->vis;
    demo->node.accept(&demo->node, vis, 0);

    return 0;
}

