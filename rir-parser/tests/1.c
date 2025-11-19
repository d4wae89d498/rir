#include "../parser.h"


int main()
{
    libdiag_setup_defaults();
    
    // TEST 1.
    int size;


    // === intlit tests ===
    rir_parser_init("12");
    size = intlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 2);

    rir_parser_init("dwa");
    size = intlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == -1);

    // === strlit tests ===
    rir_parser_init(stringify_defined("hello"));
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 7);
 
    rir_parser_init(stringify_defined("\01\xffo"));
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == 5);

    rir_parser_init("12");
    size = strlit_parser(0);
    fmt_debug("size={}", size);
    assert(size == -1);

//    std_parser_ctx->src = "4   +   13 + 4";
//    size = binop_parser(0);
//    fmt_debug("binop size={}", size);
//    assert(size == 5);

    /////



    parse_file(stringify_defined(WS_DIR) "/rir-parser/tests/1.rir");
    size = prog_parser(0);
    fmt_debug("size={}", size);
    assert(size == -1);

    return 0;
}