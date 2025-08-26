#include <rir.h>

int main() {
    prog *demo = prog();

    builder_begin(demo);
    function("main");

    block *b1 = block("b1");
    value *x1 = add(arg(2), arg(1));
    call(resolve("printf"), strlit("Result id : %d"), x1);

    block *b2 = block("b2");
    value *x2 = add(arg(2), arg(1));

    block(0);
    value *x3 = phi(x1, b1, x2, b2);

    //

    var *v1 = var("v1");
    block *c1 = block("c1");
    store(v1, intlit(12));  // value x1

    block *c2 = block("c2");
    store(v1, intlit(12));  // value x2


    block *c3 = block("c3");
    load(v1); // phi x1 c1 x2 c2  => value


    builder_end();


    
   return 0;
}

