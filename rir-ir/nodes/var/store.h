#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

struct __attribute__((packed)) store {
    instr    instr;
    var     *dest;
    value   *v;
};

visitable(node_visitor, node, store, self)

static store *store_new(var *dest, value *v) {
    return new(store, 
        .instr = instr_impl(
            .accept = &store_visit,
            .type = "store", 
        ),
        .dest = dest, 
        .v = v
    );
}

static store *Store(var *dest, value *v) {
    store *self = store_new(dest, v);
    builder_attach_instr(&self->instr);
    return self;
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H