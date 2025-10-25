
#include "parser.h"
#include "rir.h"
#include <ctype.h>
#include <stdio.h>

#define T strstack, const char*
#include <stc/stack.h>

////////////////////////////////////////////
//  BPC char* to ir implementation 
//

typedef struct ctx 
{
    size_t      match_length;
    prog        *prog;
    strstack    stack;
    const char  *src;
} ctx;

static ctx *self = 0;

void parse_str(const char *str)
{
    printf("parsing:=============\n%s\n===============\n", str);

    self = &(ctx) {
        .src = str,
        .stack = strstack_init()
    };

    printf("PARSING DONE.\n");
}

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

// === prog ===
static int prog_parser_impl(void *arg)
{
    (void) arg;
    const char *start_ptr = self->src;
    int match_size = apply(
        rep(rule(func_parser))
    );
    return match_size > 0 ? match_size : -1;
}
bpc_parser *prog_parser = &prog_parser_impl;

// === id ===
static int id_parser_impl(void *arg)
{
    (void) arg;
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
bpc_parser *id_parser = &id_parser_impl;

// === stmt_block ===
static int stmt_block_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("{"),
        rep(rule(expr_parser)),
        tk("}")
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *stmt_block_parser = &stmt_block_parser_impl;

// === func ===
static int func_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("func"),
        rule(id_parser),
        tk("("),
        opt(rep(rule(id_parser))),
        tk(")"),
        rule(stmt_block_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *func_parser = &func_parser_impl;

// === expr ===
static int expr_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        rule(binop_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *expr_parser = &expr_parser_impl;

// === ret ===
static int ret_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("return"),
        opt(rule(expr_parser))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *ret_parser = &ret_parser_impl;

// === if ===
static int if_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("if"),
        tk("("),
        rule(expr_parser),
        tk(")"),
        rule(stmt_block_parser),
        opt(seq(tk("else"), rule(stmt_block_parser)))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *if_parser = &if_parser_impl;

// === while ===
static int while_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("while"),
        tk("("),
        rule(expr_parser),
        tk(")"),
        rule(stmt_block_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *while_parser = &while_parser_impl;

// === for ===
static int for_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        tk("for"),
        tk("("),
        opt(rule(expr_parser)),
        tk(";"),
        opt(rule(expr_parser)),
        tk(";"),
        opt(rule(expr_parser)),
        tk(")"),
        rule(stmt_block_parser)
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *for_parser = &for_parser_impl;

// === binop ===
static int binop_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        rule(unaryop_parser),
        rep(seq(
            alt(tk("+"), tk("-"), tk("*"), tk("/")),
            rule(unaryop_parser)
        ))
    ));
    return match_size > 0 ? match_size : -1;
}
bpc_parser *binop_parser = &binop_parser_impl;

// === unaryop ===
static int unaryop_parser_impl(void *arg)
{
    (void) arg;
    int match_size = apply(seq(
        opt(alt(tk("+"), tk("-"), tk("!"))),
        rule(intlit_parser)
    ));
    if (match_size <= 0) 
        return -1;
    const char *tkval = *strstack_top(&self->stack);
    strstack_pop(&self->stack);
    if (!strcmp(tkval, "!")) {
        //not1();
    }
    return match_size;
}
bpc_parser *unaryop_parser = &unaryop_parser_impl;

// === intlit ===
static int intlit_parser_impl(void *arg)
{
    (void) arg;
    const char *start_ptr = self->src;
    int match_size = apply(rep(chris(isdigit)));
    if (match_size <= 0)
        return -1;
    const char *str = strndup(start_ptr, match_size);
    intlit(atoi(str));
    return match_size;
}
bpc_parser *intlit_parser = &intlit_parser_impl;

// === strlit ===
static int strlit_parser_impl(void *arg)
{
    (void) arg;
    const char *start_ptr = self->src;
    int match_size = apply(seq(
        tk("\""),
        rep(chris(isprint)),
        tk("\"")
    ));
    if (match_size <= 0)
        return -1;
    const char *str = strndup(start_ptr, match_size);
    strlit(str);
    return match_size;
}
bpc_parser *strlit_parser = &strlit_parser_impl;
