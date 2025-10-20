#include <btp2.h>

char src[] = {
#embed "test.rir"
,0
};

////////////////////////////////////////////

static bool _id()
{
    return false;
}
#define id rule(&_id)

//

static bool _stmt()
{
    return false;
}
#define stmt rule(&_stmt);

//

static plambda* _func()
{
    return or(
        rep(tk("0")),
        tk("test2")
    );
}

/////////////////////////////////////////

int main()
{
    ctx test = {
        .src = "000000test2",
    };
    self = &test;
    plambda *r = _func();
    bool result = r->p(r->arg);
    printf("result: %i\n", result);
    return 0;
}