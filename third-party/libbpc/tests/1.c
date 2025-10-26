#include <bpc.h>
#include <ctype.h>
#include <stdio.h>
#include <stcutils.h>

////////////////////////////////////////////
//  BPC char* to ir implementation 
//

typedef struct ctx 
{
    size_t      match_length;
    //  todo: irtree
    strstack    stack;
    const char  *src;
} ctx;

ctx *self= &(ctx){};

static void rir_bkp_del(void *ptr)
{
    ctx *ctx_ptr  = ptr;
    //strstack_drop(&ctx_ptr->stack);
    return;
}

static void* rir_bkp(void)
{
    return new(ctx,
        .stack = strstack_clone(self->stack),
        .src = self->src
    );
}

static void rir_bkp_restore(void* ptr)
{
    self = (ctx*)ptr;
}

static int rir_token(void* arg)
{
    const char *str = arg;
    int tklen = (int) strlen(str);
    if (!strncmp(str, self->src, tklen))
    {
        self->src += tklen;
        return tklen;
    }
    return 0;
}

static bool rir_eof(void)
{
    return (*self->src == 0);
}

static void rir_consume(void)
{
    self->src += 1;
}

static int rir_peek(void)
{
    return *self->src;
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


#define id rule(&_id)
static int _id(void*)
{
    const char *start_ptr = self->src;
    int match_size = apply(seq(
        alt(chris(isalpha), tk("_")),
        opt(rep(alt(chris(isalnum), tk("_"))))
    ));
    if (match_size <= 0)
        return -1;

    strstack_push(&self->stack, strndup(start_ptr, match_size));
    return match_size;
}

#define func rule(&_func)
static int _func(void*)
{
    int match_size = apply(seq(
        opt(tk("export")),
        id,
        tk("("),
        seq(id, opt(rep(seq(tk(","), id))),
        tk(")")
       // todo: stmt_block
    )));
    if (match_size < 0)
        return -1;
    // todo: pop first as a name, pop all remaining as arg names
    // todo: push into ir tree
    // todo: auto space skip before and after 'rule'
    return match_size;

}

/////////////////////////////////////////

char src[] = {
#embed "test.rir"
,0
};

int main()
{
    // TEST 1.

    printf("begin..\n");
    self = &(ctx) {
        .src = "_test34",
        .stack = strstack_init()
    };
    //_id(0);
    int r = apply(id);
    printf("result: %i\n", r);
    for (c_each(i, strstack, self->stack)) {
        printf("stack[]=%s\n", *i.ref);
    }
    assert(r > 0);
    assert(!strcmp(*strstack_top(&self->stack), "_test34"));
    
    // TEST 2.

    self = &(ctx) {
        .src = "export main ( ac, av )",
        .stack = strstack_init()
    };
    r = apply(func);
    printf("%d\n", r);
    for (c_each(i, strstack, self->stack)) {
        printf("stack[]=%s\n", *i.ref);
    }
    assert(r == 22);
    printf("BPC TESTS done.\n");
    return 0;
}