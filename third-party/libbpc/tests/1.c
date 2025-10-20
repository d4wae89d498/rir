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

// todo:: move this out of usercode.. 
// abstract way  to  peek / consume str ?
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
#define chris(f) plambda(&_chris, (void*)(int (*)(int))&f)
#define skipws  rep(chris(isspace))

////////////////////////////////////////////

static int _id(void*)
{
    const char *start_ptr = self->src;
    int match_size = papply(and(
        or(chris(isalpha), tk("_")),
        opt(rep(or(chris(isalnum), tk("_"))))
    ));
    if (match_size <= 0)
        return -1;

    strstack_push(&self->stack, strndup(start_ptr, match_size));
    return match_size;
}
#define id rule(&_id)

static int _func(void*)
{
    int match_size = papply(and(
        opt(tk("export")),
        id,
        tk("("),
        and(id, opt(rep(and(tk(","), id))),
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
#define func rule(&_func)

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
    
    test = (ctx) {
        .src = "export main ( ac, av )",
        .stack = strstack_init()
    };
    self = &test;
    r = papply(func);
    printf("%d\n", r);
    for (c_each(i, strstack, self->stack)) {
        printf("stack[]=%s\n", *i.ref);
    }
    assert(r == 22);
    return 0;
}