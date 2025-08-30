#ifndef RIR_ARG_H
# define RIR_ARG_H

# include "./../expr.h"

typedef struct arg
{
    expr_base
    unsigned n;
} arg;

static void *arg_visit(arg *self, hmap *vis, void *ctx) {
    trace();
    void* p = (hmap_find(vis, "arg").ref)->second;
    ir_visitor_method f = (ir_visitor_method)(uintptr_t)p;
    trace();
    return f((node*)self, ctx);
}

static value *Arg(unsigned n) {
    expr *self = new(arg, 
        .expr_type = "arg",
        .n = n,
        .accept = (ir_node_method) &arg_visit
    );
    return value(self);
}

# define arg(n) Arg(n)

#endif // RIR_ARG_H