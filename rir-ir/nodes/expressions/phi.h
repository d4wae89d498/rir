#ifndef RIR_PHI_H
# define RIR_PHI_H
# include <rir.h>

typedef struct phi
{
    expr     expr; 
    value    **values;
    block    **blocks;
    value      *dest;
    unsigned   size;
} phi;

static void *phi_accept(phi *self, node_visitor *vis, void *ctx) {
    return node_visitor_find(vis, "phi").ref->second(
        &self->expr.node,
        ctx
    );
}

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
    phi *p = new(phi, 
        .expr = {
            .node = {
                .accept = (ir_node_method) &phi_accept,
                .type = "instr"
            },
            .type = "phi"
        },
        .values = (value**)malloc(sizeof(value*) * count),
        .blocks = (block**)malloc(sizeof(block*) * count),
        .size = count,
    );
   
    if (!p->values || !p->blocks) {
        free(p->values);
        free(p->blocks);
        free(p);
        return NULL;
    }

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
    value(&p->expr);
    return NULL;
}

# define phi(...) Phi(__VA_ARGS__, 0)

#endif /* RIR_PHI_H */
