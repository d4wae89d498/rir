#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

struct ret {
    terminator  terminator;
    value       *value;
};

visitable(node_visitor, node, ret, &self->terminator.impl)

static ret *ret_new(value *value) {
    ret *self = new(ret, 
        .terminator = terminator_impl(
            .accept = &ret_visit,
            .type = "ret"
        ),
        .value = value
    );
    builder_attach_instr(&self->terminator.instr); 
    return self;
}

# define ret(x) ret_new(x)

#endif // RIR_RET_H