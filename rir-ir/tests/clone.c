
#include <rir.h>
#include <stdio.h>

int main() {
    setup();
    notice("=== testing clone ===");

    // 1. build the IR
    prog *demo = prog();
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

    notice("build done.\n");

    // 2. print it first
    print_visitor_ctx octx = {
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(demo->node, accept, print_visitor, &octx);
    notice("-----\nGenerated IR:\n-");
    dump_file(stdout, octx.ostream);
    notice("-----");

    // 3. clone it
    notice("clonning...\n");
    clone_visitor_ctx ctx = {
        .ptrmap = ptrmap_init()
    };
    prog *clone = dot(demo->node, accept, clone_visitor, &ctx);
    notice("DONE.\n");

    // 4. print the clonned ir
    print_visitor_ctx cctx = {
        .depth = 0,
        .ostream = tmpfile()
    };
    dot(clone->node, accept, print_visitor, &cctx);
    notice("-----\nClonned IR:\n-");
    dump_file(stdout, cctx.ostream);
    notice("-----");

    // 5. compare original and clonned ir
    if (!files_equal(octx.ostream, cctx.ostream)) {
        error("original and clonned ir dump differs !");
        exit(1);
    } else {
        notice("OK -- clonned and original dump are equal")
    }

    // 6. free both
    delete_visitor_ctx delete_ctx = {
        .ptrset = ptrset_init()
    };
    dot(demo->node, accept, delete_visitor, &delete_ctx);
    dot(clone->node, accept, delete_visitor, &delete_ctx);

    delete_visitor_flush(&delete_ctx);
    ptrset_drop(&delete_ctx.ptrset);

    ptrmap_drop(&ctx.ptrmap);

    fclose(octx.ostream);
    fclose(cctx.ostream);

    return 0;
}

