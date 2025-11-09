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

            call(resolve("printf"), strlit("hello %d"), x1);

            
            var *v2 = var();

            
            when(intlit(1))
                store(v2, mul2(intlit(2), intlit(4)));
            otherwise
                store(v2, add2(intlit(2), intlit(4)));
            endwhen

            call(resolve("printf"), load(v2));

            ret(x1);
    builder_end();
    printf("build done.\n");

    // 2. print it first
    print_visitor_ctx octx = {
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &octx);
    fmt_println("-----\nGenerated IR:\n-");
    dump_file(stdout, octx.ostream);
    fmt_println("-----");

    // 3. clone it
    printf("clonning...\n");
    clone_visitor_ctx ctx = {
        .ptrmap = ptrmap_init()
    };
    prog *clone = dot(demo->node, accept, clone_visitor, &ctx);
    printf("DONE.\n");

    // 4. print the clonned ir
    print_visitor_ctx cctx = {
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(clone->node, accept, print_visitor, &cctx);
    fmt_println("-----\nClonned IR:\n-");
    dump_file(stdout, cctx.ostream);
    fmt_println("-----");

    // 5. compare original and clonned ir
    if (!files_equal(octx.ostream, cctx.ostream)) {
        error("original and clonned ir dump differs !");
        exit(1);
    }
    
    return 0;
}

