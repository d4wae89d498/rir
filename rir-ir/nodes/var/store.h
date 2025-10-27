#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

struct store {
    instr    instr;
    var     *dest;
    value   *v;
};

visitable(node_visitor, node, store, &self->instr.impl)

static void Store(var *dest, value *v) 
{
    store *self = new(store, 
        .instr = instr_impl(
            .accept = &store_visit,
            .type = "store", 
        ),
        .dest = dest, 
        .v = v
    );
    builder_attach_instr(&self->instr);
    return;
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H