#ifndef RIR_LOAD_H
# define RIR_LOAD_H
# include <rir.h>

struct load {
    expr    expr;
    var     *v;
};

visitable(node_visitor, node, load, &self->expr.impl)

static value *Load(var *v) 
{
    load *self = new(load, 
        .expr = expr_impl(
            .accept = &load_visit,
            .type = "load"
        ), 
        .v = v
    );
    return value(&self->expr);
}

# define load(v) Load(v)

#endif // RIR_LOAD_H