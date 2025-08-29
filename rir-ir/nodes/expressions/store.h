#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

typedef struct store {
    instr_base
    var *dest;
    value *v;
} store;

value *Store(var *dest, value *v) 
{
    instr *self = new(store, 
        .instr_type = "store", 
        .dest = dest, 
        .v = v
    );

    block *b = builder_get_block();
    // todo: push self
    return 0;
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H