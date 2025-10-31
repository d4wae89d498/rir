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

# define ret(x) builder_attach_instr(&ret_new(x)->terminator.instr); 

#endif // RIR_RET_H