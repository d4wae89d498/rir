#ifndef RIR_VALUE_H
# define RIR_VALUE_H
# include "expr.h"
# include "instr.h"

typedef struct value {
    instr_base

    int     id;
    expr    *e;
} value;


static void *value_visit(value *self, hmap *vis, void *ctx) {
    trace();
    void* p = (hmap_find(vis, "value").ref)->second;
    fprintf(stderr, "-> %p\n", p);
    ir_visitor_method f = (ir_visitor_method)(uintptr_t)p;
    trace();
    return f((node*)self, ctx);
}

static value *Value(expr *e) {
    static int nb;

    nb++;

    instr *out = new(value, 
        .e = e,
        .id = nb,
        .prev = 0,
        .next = 0,
        .accept = (ir_node_method) &value_visit
    );
    instr(out);
   
    return (value*)out;
}

# define value(v) Value(v)


#endif // RIR_VALUE_H