#include <rir.h>


int main() {
    setup();
    fmt_println("=== testing clone ===");

    // 1. build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *x1 = add2(intlit(2), intlit(4));
            var *v1 = var();
            store(v1, x1);
         
         
            /*call(resolve("printf"), strlit("hello %d"), intlit(2));
            block *true_case;
            block *false_case;
            var *v2 = var();
            true_case = block("true_case");
            store(v2, mul2(intlit(2), intlit(4)));
            false_case = block("false_case");
            store(v2, add2(intlit(2), intlit(4)));
            when(intlit(1), true_case, false_case);
            call(resolve("printf"), load(v2));*/
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

