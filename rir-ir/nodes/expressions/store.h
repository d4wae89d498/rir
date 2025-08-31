#ifndef RIR_STORE_H
# define RIR_STORE_H
# include <rir.h>

typedef struct store {
    instr instr;
    var *dest;
    value *v;
} store;

value *Store(var *dest, value *v) 
{
    store *self = new(store, 
        .instr = {
            .type = "store", 
        },
        .dest = dest, 
        .v = v
    );
    instr(&self->instr);
    return 0;
}

# define store(d, v) Store(d, v)

#endif // RIR_STORE_H