#ifndef RIR_LOAD_H
# define RIR_LOAD_H
# include <rir.h>

typedef struct load {
    instr_base
    var *v;
} load;

value *Load(var *v) 
{
    instr *self = new(load, 
        .instr_type = "store", 
        .v = v
    );
    return 0;
}

# define load(v) Load(v)

#endif // RIR_LOAD_H