#ifndef BTP2_H
# define BTP2_H
#include <stddef.h>
# include <string.h>
# include <sugar.h>

# define papply(plambda) (plambda)->p((plambda)->arg)

typedef struct ctx {
    const char *src;
} ctx;

ctx *self;

typedef bool (parser)(void *arg);

typedef struct plambda
{
    parser  *p;
    void    *arg;
} plambda;
# define plambda(A, B) new(plambda, A, B)

bool _tk(void *arg)
{
    const char *str = arg;
    size_t tklen = strlen(str);
    bool r = !strncmp(str, self->src, tklen);
    if (r)
    {
        self->src += tklen;
        return true;
    }
    return false;
}

// TODO: maybe take the longest match
bool _or(void *arg)
{
    plambda** lambdas = (plambda**)arg;
    size_t i =  0;
    while (lambdas[i])
    {
        if (papply(lambdas[i]))
            return true;
        i += 1;
    }
    return false;
}

bool _and(void *arg)
{
    plambda** lambdas = (plambda**)arg;
    size_t i =  0;
    while (lambdas[i])
    {
        if (!papply(lambdas[i]))
            return false;
        i += 1;
    }
    return true;
}

bool _opt(void *arg)
{
    plambda* lambda = (plambda*)arg;
    papply(lambda);
    return true;
}

bool _rep(void *arg)
{
    plambda* lambda = (plambda*)arg;
    if (!papply(lambda))
        return false;
    while (papply(lambda))
        ;
    return true;
}

# define rule(N) plambda(N, 0)
# define tk(T) plambda(&_tk, T)
# define opt(R) plambda(&_opt, T)
# define rep(R) plambda(&_rep, R)
# define and(...) plambda(&_and, \
    ((plambda*)(_new(\
                sizeof(\
                    (plambda*[]){__VA_ARGS__, 0}\
                ),\
                &(plambda*[]){__VA_ARGS__, 0}\
    ))))

# define or(...) plambda(&_or, \
    ((plambda*)(_new(\
                sizeof(\
                    (plambda*[]){__VA_ARGS__, 0}\
                ),\
                &(plambda*[]){__VA_ARGS__, 0}\
    ))))

#endif