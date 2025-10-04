#include <rir.h>


int main() {
    fmt_println("==== testing vars ====");

    // Build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *x1 = add2(intlit(2), intlit(4));
            var *v1 = var();

            store(v1, x1);

            call(resolve("printf"), strlit("hello %d"), intlit(2));
            
            block *true_case;
            block *false_case;
            var *v2 = var();
            
            true_case = block("true_case");
            store(v2, mul2(intlit(2), intlit(4)));
            false_case = block("false_case");
            store(v2, add2(intlit(2), intlit(4)));

            when(intlit(1), true_case, false_case);

            call(resolve("printf %d\n"), load(v2));

            ret(x1);
    builder_end();

    // Print it
    setup_targets();
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
    dump_file_to(ctx.ostream, stdout);
    fmt_println("-----");
    fmt_println("Exiting... {}\n", (void*)visitor);
    return 0;
}

