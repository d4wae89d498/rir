#include "stc/common.h"
#include <bpc.h>
#include <ctype.h>

char src[] = {
#embed "test.rir"
,0
};

#define T strstack, const char*
#include <stc/stack.h>

typedef struct ctx 
{
    size_t      match_length;
    //  todo:irtree
    strstack    stack;
    const char  *src;
} ctx;

ctx ctx_data;
ctx *self= &ctx_data;

static void my_del(void *ptr)
{
    ctx *ctx_ptr  = ptr;
    //strstack_drop(&ctx_ptr->stack);
    return;
}

static void* my_backup()
{
    return new(ctx,
        .stack = strstack_clone(self->stack),
        .src = self->src
    );
}

static void my_restore(void* ptr)
{
    self = (ctx*)ptr;
}

static int my_token(const char *str)
{
    int tklen = (int) strlen(str);
    if (!strncmp(str, self->src, tklen))
    {
        self->src += tklen;
        return tklen;
    }
    return 0;
}

// btp_tk_match()

////////////////////////////////////////////

static int _chris(void* arg)
{
    int (*f)(int) = (int (*)(int))arg;
    int output;

    if (!f(*self->src))
    {
        return -1;
    }
    output = 1;
    self->src += 1;
    while(f(*self->src))
    {
        output += 1;
        self->src += 1;
    }
    return output;
}
#define chris(f) plambda(&_chris, (void*)(bool (*)(int))&f)

static int _id(void*)
{
    const char *start_ptr = self->src;
    int match_size = papply(and(
        or(chris(isalpha), tk("_")),
        opt(rep(or(chris(isalnum), tk("_"))))
    ));
    if (match_size > 0) {
        strstack_push(&self->stack, strndup(start_ptr, match_size));
        return match_size;
    }
    return -1;
}
#define id rule(&_id)


/////////////////////////////////////////

int main()
{
    _bpc_backup = &my_backup;
    _bpc_restore = &my_restore;
    _bpc_token = &my_token;
    _bpc_del = &my_del;

    ctx test = {
        .src = "_test34",
        .stack = strstack_init()
    };
    self = &test;
    int r = papply(id);
    printf("result: %i\n", r);
    for (c_each(i, strstack, self->stack)) {
        printf("stack[]=%s\n", *i.ref);
    }
    assert(!strcmp(*strstack_top(&self->stack), "_test34"));
    return 0;
}