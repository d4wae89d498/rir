
#include <rir.h>

////////////////////////////////////////////
//  BPC char* to ir implementation 
//

// 
parser_ctx *std_parser_ctx = 0;

//
cstrstack   csstack;
strstack    sstack;
nodestack   nstack;

void rir_parser_init(const char *src) {

    csstack = cstrstack_init();
    sstack = strstack_init();
    nstack = nodestack_init();

    
    std_parser_ctx = new(parser_ctx,
        .csstack_size = 0,
        .sstack_size = 0,
        .nstack_size = 0,

        .block_id = 0,
        .temp_id = 0,
        .var_id = 0,

        .path = 0,
        .src = src,

        .line = 1,
        .col = 1,

    );
}

//////


#define MAX_FILE_SIZE 4*1024*1024 // 4MB max for a source file seems large enough
void parse_file(const char *path)
{
    if (!path)
    {
        error("Path cant be null");
        exit(1);
    }

    const char *mode = "r";
    FILE *file = fopen(path, mode);
    if (!file)
    {
        error("Unable to open '%s' in mode '%s'", path, mode);
        exit(1);
    }

    char *buf = malloc(MAX_FILE_SIZE + 1);
    if (!buf) { 
        fclose(file); 
        error("Allocation error, unable to allocate %d bytes.", MAX_FILE_SIZE + 1);
        exit(1);
    }

    size_t n = fread(buf, 1, MAX_FILE_SIZE, file);
    fclose(file);

    if (n == MAX_FILE_SIZE && !feof(file)) {
        error("Input file %s is too big, unable to parse it.", path);
        free(buf);
        return;
    }

    buf[n] = '\0';
    debug("=== parsing file ===\n%s\n========", buf);
    rir_parser_init(buf);
    std_parser_ctx->path = strdup(path);
}

//////


static void rir_bkp_del(void *ptr)
{
    //strstack_drop(&ctx_ptr->stack);
    return;
}

static void* rir_bkp(void)
{
    // todo: do  not clone / restore stack 
    // -> remove last n elements pushed since last backup
    return new(parser_ctx,
        .temp_id = temp_id,
        .var_id = var_id,
        .block_id = block_id,

        .csstack_size = cstrstack_size(&csstack),
        .sstack_size = strstack_size(&sstack),
        .nstack_size = nodestack_size(&nstack),

        .path = std_parser_ctx->path,
        .src = std_parser_ctx->src,


        .line = std_parser_ctx->line,
        .col = std_parser_ctx->col
    );
}

static parser_ctx* rir_bkp_clone(parser_ctx *bkp)
{
    return new(parser_ctx,
        .temp_id = bkp->temp_id,
        .var_id = bkp->var_id,
        .block_id = bkp->block_id,

        .csstack_size = bkp->csstack_size,
        .sstack_size = bkp->sstack_size,
        .nstack_size = bkp->nstack_size,

        .path = bkp->path,
        .src = bkp->src,

        .line = bkp->line,
        .col = bkp->col
    
    );
}

static void rir_bkp_restore(void* ptr)
{
    parser_ctx *bkp = (parser_ctx*)ptr;


    int csstack_size_diff = cstrstack_size(&csstack) - bkp->csstack_size;
    if (csstack_size_diff > 0)
        while (csstack_size_diff--)
            cstrstack_pop(&csstack);

    int sstack_size_diff = strstack_size(&sstack) - bkp->csstack_size;
    if (sstack_size_diff > 0)
        while (sstack_size_diff--)
            strstack_pop(&sstack);

    int nstack_size_diff = nodestack_size(&nstack) - bkp->csstack_size;
    if (nstack_size_diff > 0)
        while (nstack_size_diff--)
            nodestack_pop(&nstack);

    temp_id = bkp->temp_id;
    var_id = bkp->var_id;
    block_id = bkp->block_id;

    free(std_parser_ctx);

    std_parser_ctx = rir_bkp_clone(bkp);

}

static void rir_consume(int len)
{
    debug("consume %d", len);
    if (std_parser_ctx->src[0] == '\n')
    {
        std_parser_ctx->line += 1;
        std_parser_ctx->col = 1;
    } else {
        std_parser_ctx->col += 1;
    }
    std_parser_ctx->src += len;
}

static int rir_punctuation(void* arg)
{
    const char *str = arg;
    int punclen = (int) strlen(str);
    if (!strncmp(str, std_parser_ctx->src, punclen))
    {
        debug("accepted punc %s [%d]", str, punclen);
        rir_consume(punclen);
        return punclen;
    }
    return 0;
}

static int rir_token(void* arg)
{

    int tklen = rir_punctuation(arg);
    if (tklen <= 0)
        return -1;
    cstrstack_push(&csstack, (const char*)arg);
    return tklen;
}

static bool rir_eof(void)
{
    return (*std_parser_ctx->src == 0);
}

static int rir_peek(void)
{
    return *std_parser_ctx->src;
}

bpc_implementation *bpc = &(bpc_implementation) {
    .token = &rir_token,
    .punctuation = &rir_punctuation,
    .bkp = &rir_bkp,
    .bkp_restore = &rir_bkp_restore,
    .bkp_del = &rir_bkp_del,
    .eof = &rir_eof,
    .consume = &rir_consume,
    .peek = &rir_peek
};

////////////////////////////////////////////
// BPC language specifics

