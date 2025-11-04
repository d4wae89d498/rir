#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

struct ret {
    terminator  terminator;
    value       *value;
};

visitable(node_visitor, node, ret, &self->terminator.impl)

static ret *ret_new(value *value) {
    return new(ret, 
        .terminator = terminator_impl(
            .accept = &ret_visit,
            .type = "ret"
        ),
        .value = value
    );
}

static ret *Ret(value *value) {
    ret *self = ret_new(value);
    builder_attach_instr(&self->terminator.instr); 
    return self;
}

# define ret(x) Ret(x)

#endif // RIR_RET_H