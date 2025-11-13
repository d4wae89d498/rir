#ifndef BPC_H
# define BPC_H
# include <stddef.h>
# include <string.h>
# include <sugar.h>

typedef int (bpc_parser)(void*);

typedef struct bpc_implementation
{
    bpc_parser *token;
    bpc_parser *punctuation;
    void    *(*bkp)(void);
    void    (*bkp_restore)(void*);
    void    (*bkp_del)(void*);
    bool    (*eof)(void);
    void    (*consume)(int);
    int     (*peek)(void);
} bpc_implementation;

extern bpc_implementation *bpc;

# define tk(T) closure(&_tk, T)
static int _tk(void *arg)
{
    int size;
    void *backup = bpc->bkp();
    size = bpc->token(arg);
    if (!size) {
        bpc->bkp_restore(backup);
        size = -1;
    }
    bpc->bkp_del(backup);
    return size;
}

# define punc(T) closure(&_punc, T)
static int _punc(void *arg)
{
    int size;
    void *backup = bpc->bkp();
    size = bpc->punctuation(arg);
    if (!size) {
        bpc->bkp_restore(backup);
        size = -1;
    }
    bpc->bkp_del(backup);
    return size;
}


# define alt(...) closure(&_alt, \
    ((closure*)(_new(\
                sizeof(\
                    (closure*[]){__VA_ARGS__, 0}\
                ),\
                &(closure*[]){__VA_ARGS__, 0}\
    ))))
static int _alt(void *arg)
{
    void *initial = bpc->bkp();
    void *longest_match_bkp = 0;
    int longest_match = -1;
    int current_match;

    closure** cls = (closure**)arg;
    int i =  0;
    while (cls[i])
    {
        current_match = apply(cls[i]);
        if (current_match > longest_match) {
            bpc->bkp_del(longest_match_bkp);
            longest_match_bkp = bpc->bkp();
            longest_match = current_match;
        }
        bpc->bkp_restore(initial);
        i += 1;
    }

    if (longest_match_bkp)
        bpc->bkp_restore(longest_match_bkp);
    return longest_match;
}


# define seq(...) closure(&_seq, \
    ((closure*)(_new(\
                sizeof(\
                    (closure*[]){__VA_ARGS__, 0}\
                ),\
                &(closure*[]){__VA_ARGS__, 0}\
    ))))
static int _seq(void *arg)
{
    int match_size = 0;
    int candidate = 0;
    void *backup = bpc->bkp();
    closure** cls = (closure**)arg;
    int i =  0;
    while (cls[i])
    {
        candidate = apply(cls[i]);
        if (candidate < 0)
        {
            bpc->bkp_restore(backup);
            return -1;
        }
        match_size += candidate;
        i += 1;
    }
    bpc->bkp_del(backup);
    return match_size;
}

# define opt(R) closure(&_opt, R)
static int _opt(void *arg)
{
    closure* cl = (closure*)arg;
    int out = apply(cl);
    if (out < 0)
        out = 0;
    return out;
}

# define rep(R) closure(&_rep, R)
static int _rep(void *arg)
{
    closure* cl = (closure*)arg;
    int out = 0;
    int candidate;
    while (1)
    {
        candidate = apply(cl);
        if (candidate < 0)
            break;
        out += candidate;
    }
    if (out == 0)
        out = -1;
    return out;
}

# define toggle(R) closure(&_toggle, R)
static int _toggle(void *ptr) {
    bool *v = ptr;
    *v = true;
    return 0;
}

struct setval_ctx {
    int *ptr;
    int value;
};

# define setval(P, V) closure(&_setval, (&(struct setval_ctx){P, V}) )
static int _setval(void *ptr) {
    struct setval_ctx *self = (struct setval_ctx*) ptr;
    *self->ptr = self->value;
    return 0;
}

# define rule(N) seq(opt(skipws), closure(N, 0), opt(skipws))
# define skipws  rep(chris(isspace))
# define chris(f) closure(&_chris, (void*)(int (*)(int))&f)
static int _chris(void* arg)
{
    int (*f)(int) = (int (*)(int))arg;
    int output;

    if (bpc->eof() || !f(bpc->peek()))
    {
        return -1;
    }
    output = 1;
    bpc->consume(1);    
    while(!bpc->eof() && f(bpc->peek()))
    {
        output += 1;
        bpc->consume(1);
    }
    return output;
}

# define orep(x) opt(rep(x))

#endif // BPC_H