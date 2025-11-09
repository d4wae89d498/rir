
#include <rir.h>

int main() {
    setup();
    notice("=== testing interpret (simple) ===");

    prog *demo = prog();
    function("main");
        value *x1 = add2(intlit(1), intlit(2));
        value *x2 = mul2(x1, intlit(3));
        ret(x2);

    interpret_ctx ctx = {
        .ptrmap = ptrmap_init()
    };
    long result = (long) dot(demo->node, accept, interpret_visitor, &ctx);
    notice("result=%ld", result);
    assert(result == 9);
}