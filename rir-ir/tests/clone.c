#include <rir.h>


int main() {
    setup();
    fmt_println("=== testing clone ===");

    // 1. build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *const x1 = add2(intlit(2), intlit(4));
            var *v1 = var();
            store(v1, x1);
            ret(x1);
    builder_end();
    printf("build done.\n");

    // 2. print it first
    auto ctx = (print_target_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &ctx);
    fmt_println("-----\nGenerated IR:\n-");
    dump_file(stdout, ctx.ostream);
    fmt_println("-----");

    // 3. clone it
    printf("clonning...\n");
    prog *clone = dot(demo->node, accept, clone_visitor, &ctx);
    printf("DONE.\n");

    // 4. print the clonned ir
    ctx = (print_target_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(clone->node, accept, print_visitor, &ctx);
    fmt_println("-----\nClonned IR:\n-");
    dump_file(stdout, ctx.ostream);
    fmt_println("-----");
    return 0;
}

