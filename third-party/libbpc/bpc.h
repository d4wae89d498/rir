#ifndef BTP2_H
# define BTP2_H
#include <stddef.h>
# include <string.h>
# include <sugar.h>

# define papply(fu) (fu)->p((fu)->arg)


typedef int (*parser)(void *arg);

typedef struct plambda
{
    parser  p;
    void    *arg;
} plambda;
# define plambda(A, B) new(plambda, A, B)


int (*_bpc_token)(const  char *);
void (*_bpc_restore)(void*);
void (*_bpc_del)(void*);
void *(*_bpc_backup)();

int _tk(void *arg)
{
    int size;
    void *backup = _bpc_backup();
    const char *str = arg;
    size = _bpc_token(str);
    if (!size) {
        _bpc_restore(backup);
        size = -1;
    }
    _bpc_del(backup);
    return size;
}

int _or(void *arg)
{
    void *initial = _bpc_backup();
    void *longest_match_bkp = 0;
    int longest_match = -1;
    int current_match;

    plambda** lambdas = (plambda**)arg;
    int i =  0;
    while (lambdas[i])
    {
        current_match = papply(lambdas[i]);
        if (current_match > longest_match) {
            _bpc_del(longest_match_bkp);
            longest_match_bkp = _bpc_backup();
            longest_match = current_match;
        }
        _bpc_restore(initial);
        i += 1;
    }

    if (longest_match_bkp)
        _bpc_restore(longest_match_bkp);
    return longest_match;
}

int _and(void *arg)
{
    int match_size = 0;
    int candidate = 0;
    void *backup = _bpc_backup();
    plambda** lambdas = (plambda**)arg;
    int i =  0;
    while (lambdas[i])
    {
        candidate = papply(lambdas[i]);
        if (candidate < 0)
        {
            _bpc_restore(backup);
            _bpc_del(backup);
            return -1;
        }
        match_size += candidate;
        i += 1;
    }
    _bpc_del(backup);
    return match_size;
}

int _opt(void *arg)
{
    plambda* lambda = (plambda*)arg;
    int out = papply(lambda);
    if (out < 0)
        out = 0;
    return out;
}

int _rep(void *arg)
{
    plambda* lambda = (plambda*)arg;
    int out = 0;
    int candidate;
    while (1)
    {
        candidate = papply(lambda);
        if (candidate < 0)
            break;
        out += candidate;
    }
    if (out == 0)
        out = -1;
    return out;
}

# define rule(N) plambda(N, 0)
# define tk(T) plambda(&_tk, T)
# define opt(R) plambda(&_opt, R)
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