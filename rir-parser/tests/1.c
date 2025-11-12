#include "../parser.h"

char src[] = {
#embed  "1.rir"
, 0
};

int main()
{
    // TEST 1.
    int size;

    // === intlit tests ===
    std_parser_ctx->src = "12";
    size = intlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 2);

    std_parser_ctx->src = "dwa";
    size = intlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == -1);

    // === strlit tests ===
    std_parser_ctx->src = stringify_defined("hello");
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 7);
 
    std_parser_ctx->src = stringify_defined("\01\xffo");
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 5);

    std_parser_ctx->src = "12";
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == -1);

//    std_parser_ctx->src = "4   +   13 + 4";
//    size = binop_parser(0);
//    fmt_debug("binop size={}", size);
//    assert(size == 5);

    /////

    notice("parsing:=============\n%s\n===============\n", src);
    debug("TODO")

    return 0;
}