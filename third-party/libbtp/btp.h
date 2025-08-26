/*
 * btp.h
 * Back-Tracked Parsing (BTP) — tiny flexible backtracking helpers for recursive
 * descent grammars.
 */

#ifndef BTP_H
#define BTP_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include <sugar.h>
#define T PtrStack, void*
#include <stc/stack.h>


/** Opaque forward declaration for parser rule functions.
 *
 * A grammar rule is a C function that receives a Parser pointer and returns
 * true on success (consuming input and/or producing side-effects) and false
 * on failure. Rules should use the btp_* helpers when manipulating parser
 * state so backtracking remains correct.
 */
struct Parser;
typedef bool (*btp_rule)(struct Parser *p);

/** A checkpoint snapshot used for backtracking. Safe to store by-value.
 *
 * Notes:
 *  - This low-level mark captures input position (pos/line/column).
 *  - Composition primitives (btp_choice, btp_sequence, btp_rule, etc.)
 *    automatically snapshot and restore additional ephemeral parser state
 *    such as the value_stack length; use btp_mark/btp_restore for manual
 *    low-level control only when needed.
 */
typedef struct btp_backup {
    size_t pos;      /* byte index into the input buffer */
    unsigned line;   /* 1-based line number */
    unsigned column; /* 1-based column (byte offset) */
} btp_backup;

/** User-supplied typed parser declaration. 
 *
 * The user may copy-paste this or include it via the header to define a 
 * typed parser struct whose memory layout matches the library's 
 * expectations. 
 */
#define BTP_DECLARE_PARSER(name, UserType)                                \
    typedef struct name {                                                 \
        const char *input; size_t input_len;                              \
        size_t pos; unsigned line, column;                                \
        UserType *user_data;                                              \
        btp_backup *mark_stack; size_t mark_stack_len, mark_stack_cap;    \
        void **value_stack; size_t value_stack_len, value_stack_cap;      \
        char *error_msg; size_t error_pos; unsigned error_line, error_column; \
    } name;

BTP_DECLARE_PARSER(Parser, void*)

/* --- Public API macros that cast a typed parser (or the canonical Parser*) --- */
/* Users call btp_sequence(p, ...); this macro casts `p` to Parser* for the impl. */
#define btp_init(p, i, l, c)           btp_init_impl((Parser *)(p), i, l, c)
#define btp_sequence(p, ...)           btp_sequence_impl((Parser *)(p), __VA_ARGS__)
#define btp_choice(p, ...)             btp_choice_impl((Parser *)(p), __VA_ARGS__)
#define btp_rule(p, r)                 btp_rule_impl((Parser *)(p), &(r))
#define btp_optional(p, r)             btp_optional_impl((Parser *)(p), &(r))
#define btp_push_val(p, v)             btp_push_val_impl((Parser *)(p), (v))
#define btp_truncate_values(p,n)       btp_truncate_values_impl((Parser *)(p),(n))
#define btp_token(p,s)                 btp_token_impl((Parser *)(p),(s))
#define btp_set_errorf(p,pos,fmt,...)  btp_set_errorf_impl((Parser*)(p),(pos),(fmt),__VA_ARGS__)




static inline bool btp_init_impl(Parser *p, const char *input, size_t len, void *user_data) {
    p->input = input;
    p->input_len = len;
    p->line = 1;
    p->column = 1;
    p->pos = 0;
    p->user_data = user_data;

    return true;
}

/* low-level mark helpers (pos/line/column) */
static inline btp_backup btp_save(Parser *p) {
    btp_backup m = { p->pos, p->line, p->column };
    return m;
}

static inline void btp_restore(Parser *p, btp_backup m) {
    p->pos = m.pos;
    p->line = m.line;
    p->column = m.column;
}

/* peek and consume */
static inline const char *btp_peek(Parser *p) {
    if (p->input == NULL) return NULL;
    if (p->input_len && p->pos >= p->input_len) return NULL;
    if (!p->input_len && p->input[p->pos] == '\0') return NULL;
    return p->input + p->pos;
}

static inline bool btp_consume(Parser *p, size_t n) {
    /* simple byte-advance; update line/column on newlines for text inputs */
    size_t i;
    for (i = 0; i < n; ++i) {
        const char *c = btp_peek(p);
        if (!c) return false;
        if (*c == '\n') { p->line++; p->column = 1; }
        else { p->column++; }
        p->pos++;
    }
    return true;
}

/* value-stack helpers (impl) */
static inline void btp_push_val_impl(Parser *p, void *value) {
    if (p->value_stack_len >= p->value_stack_cap) {
        size_t newcap = p->value_stack_cap ? p->value_stack_cap * 2 : 16;
        void **newbuf = realloc(p->value_stack, newcap * sizeof(void*));
        if (!newbuf) return; /* OOM -> drop push (real code should signal) */
        p->value_stack = newbuf;
        p->value_stack_cap = newcap;
    }
    p->value_stack[p->value_stack_len++] = value;
}

static inline void btp_truncate_values_impl(Parser *p, size_t new_len) {
    if (new_len <= p->value_stack_len) {
        /* NOTE: does not free values; TODO: use destructors... */
        p->value_stack_len = new_len;
    }
}

//////////////////////////////////////////////////////////////////

/* variadic sequence: all rules must succeed */
static inline bool btp_sequence_impl(Parser *p, ...) {
    size_t saved_pos = p->pos;
    unsigned saved_line = p->line;
    unsigned saved_col = p->column;
    size_t saved_vals = p->value_stack_len;

    va_list ap;
    va_start(ap, p);
    btp_rule r;
    bool ok = true;
    while ((r = va_arg(ap, btp_rule)) != NULL) {
        if (!r(p)) {
            ok = false;
            break;
        }
    }
    va_end(ap);

    if (!ok) {
        /* restore both input and value stack length */
        p->pos = saved_pos;
        p->line = saved_line;
        p->column = saved_col;
        btp_truncate_values_impl(p, saved_vals);
        return false;
    }
    return true;
}

/* choice: try alternatives until one succeeds */
static inline bool btp_choice_impl(Parser *p, ...) {
    va_list ap;
    va_start(ap, p);
    btp_rule r;
    bool any = false;

    while ((r = va_arg(ap, btp_rule)) != NULL) {
        size_t saved_pos = p->pos;
        unsigned saved_line = p->line;
        unsigned saved_col = p->column;
        size_t saved_vals = p->value_stack_len;

        if (r(p)) { any = true; break; }

        /* restore and try next */
        p->pos = saved_pos;
        p->line = saved_line;
        p->column = saved_col;
        btp_truncate_values_impl(p, saved_vals);
    }
    va_end(ap);
    return any;
}

/* attempt: save once, run rule, restore on failure */
static inline bool btp_rule_impl(Parser *p, btp_rule rule) {
    size_t saved_pos = p->pos;
    unsigned saved_line = p->line;
    unsigned saved_col = p->column;
    size_t saved_vals = p->value_stack_len;

    if (!rule(p)) {
        p->pos = saved_pos;
        p->line = saved_line;
        p->column = saved_col;
        btp_truncate_values_impl(p, saved_vals);
        return false;
    }
    return true;
}

static inline bool btp_optional_impl(Parser *p, btp_rule rule) {
    btp_rule_impl(p, rule);
    return true;
}


/* simple match string */
static inline bool btp_token_impl(Parser *p, const char *string) {
    if (!string) return false;
    const char *cur = btp_peek(p);
    if (!cur) return false;

    size_t len = strlen(string);
    /* respect input_len if provided */
    if (p->input_len) {
        if (p->pos + len > p->input_len) return false;
    } else {
        /* ensure enough bytes in NUL-terminated string */
        if (strncmp(cur, string, len) != 0) return false;
    }
    if (strncmp(cur, string, len) == 0) {
        return btp_consume(p, len);
    }
    return false;
}

/* minimal error formatting (shell implementation) */
static inline void btp_set_errorf_impl(Parser *p, size_t pos, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    va_list ap2; va_copy(ap2, ap);
    int needed = vsnprintf(NULL, 0, fmt, ap2);
    va_end(ap2);
    if (needed < 0) { va_end(ap); return; }
    char *buf = (char*)malloc((size_t)needed + 1);
    if (!buf) { va_end(ap); return; }
    vsnprintf(buf, (size_t)needed + 1, fmt, ap);
    va_end(ap);

    free(p->error_msg);
    p->error_msg = buf;
    p->error_pos = pos;
    /* optionally compute line/column from pos, here set to current */
    p->error_line = p->line;
    p->error_column = p->column;
}



#endif
