#include <rir.h>


int main() {
    setup();
    fmt_println("=== testing vars ===");

    // 1. build the IR
    prog *demo = prog();
    builder_begin(demo);
        function("main");
            value *x1 = add2(intlit(2), intlit(4));
            var *v1 = var();

            store(v1, x1);

            call(resolve("printf"), strlit("hello %d"), intlit(2));
            
            var *v2 = var();
            

            when(intlit(1));
                store(v2, mul2(intlit(2), intlit(4)));
            otherwise
                store(v2, add2(intlit(2), intlit(4)));
            endwhen
            
            call(resolve("printf"), load(v2));

            ret(x1);
    builder_end();

    // 2. print it    
    auto ctx = (print_visitor_ctx){
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &ctx);
    fmt_println("-----\nGenerated IR:\n-");
    dump_file(stdout, ctx.ostream);
    return 0;
}

