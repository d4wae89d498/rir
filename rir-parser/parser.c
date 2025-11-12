
#include <rir.h>

////////////////////////////////////////////
//  BPC char* to ir implementation 
//

parser_ctx *std_parser_ctx = &(parser_ctx){};


void rir_set_src(const char *src) {
    std_parser_ctx->src = src;
}

static void rir_bkp_del(void *ptr)
{
    //strstack_drop(&ctx_ptr->stack);
    return;
}

static void* rir_bkp(void)
{
    return new(parser_ctx,
        .stack = strstack_clone(std_parser_ctx->stack),
        .src = std_parser_ctx->src
    );
}

static void rir_bkp_restore(void* ptr)
{
    std_parser_ctx = (parser_ctx*)ptr;
}

static int rir_token(void* arg)
{
    const char *str = arg;
    int tklen = (int) strlen(str);
    if (!strncmp(str, std_parser_ctx->src, tklen))
    {
        std_parser_ctx->src += tklen;
        return tklen;
    }
    return 0;
}

static bool rir_eof(void)
{
    return (*std_parser_ctx->src == 0);
}

static void rir_consume(void)
{
    std_parser_ctx->src += 1;
}

static int rir_peek(void)
{
    return *std_parser_ctx->src;
}

bpc_implementation *bpc = &(bpc_implementation) {
    .token = &rir_token,
    .bkp = &rir_bkp,
    .bkp_restore = &rir_bkp_restore,
    .bkp_del = &rir_bkp_del,
    .eof = &rir_eof,
    .consume = &rir_consume,
    .peek = &rir_peek
};

////////////////////////////////////////////
// BPC language specifics

