#ifndef RIR_PHI_H
# define RIR_PHI_H
# include <rir.h>

typedef struct phi
{
    expr     expr; 
    value    **values;
    block    **blocks;
    unsigned   size;
} phi;

static value *Phi(value *v1, block *b2, ...)
{
    if (!v1 || !b2) {
        // TODO: error: impair
        return NULL;
    }
    va_list ap;
    unsigned count = 1; 

    /* First pass: count remaining pairs until a NULL value sentinel is found */
    va_start(ap, b2);
    for (;;) {
        value *v = va_arg(ap, value*); 
        if (!v) 
            break;
        (void) va_arg(ap, block*);
        ++count;
    }
    va_end(ap);
    phi *p = (phi*)calloc(1, sizeof(phi));
    if (!p)
        return NULL;
    p->values = (value**)malloc(sizeof(value*) * count);
    p->blocks = (block**)malloc(sizeof(block*) * count);
    if (!p->values || !p->blocks) {
        free(p->values);
        free(p->blocks);
        free(p);
        return NULL;
    }
    p->size = count;

    /* second pass: fill arrays (first slot from fixed args) */
    p->values[0] = v1;
    p->blocks[0] = b2;
    va_start(ap, b2);
    unsigned i = 1;
    for (;;) {
        value *v = va_arg(ap, value*);
        if (!v) break;
        block *b = va_arg(ap, block*);
        p->values[i] = v;
        p->blocks[i] = b;
        ++i;
    }
    va_end(ap);
    return 0; // TODO: make a new value and decorate
}

# define phi(...) Phi(__VA_ARGS__, 0)

#endif /* RIR_PHI_H */
