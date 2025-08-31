#ifndef RIR_LOAD_H
# define RIR_LOAD_H
# include <rir.h>

typedef struct load {
    instr   instr;
    var     *v;
} load;

value *Load(var *v) 
{
    load *self = new(load, 
        .instr = {
            .type = "store",
        }, 
        .v = v
    );
    instr(&self->instr);
    return 0;
}

# define load(v) Load(v)

#endif // RIR_LOAD_H