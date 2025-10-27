#ifndef RIR_UNREACHABLE_H
# define RIR_UNREACHABLE_H
# include <rir.h>

struct unreachable {
    terminator terminator;
};

visitable(node_visitor, node, unreachable, &self->terminator.impl)

static ret *unreachable_new(void) {
    ret *self = new(ret, 
        .terminator = terminator_impl(
            .accept = &unreachable_visit,
            .type = "unreachable",
        ),
    );
    builder_attach_instr(&self->terminator.instr); 
    return self;
}
#undef unreachable // maybe def in __stddef_unreachable... todo: checkwhy or rename..
#define unreachable() unreachable_new()

#endif // RIR_UNREACHABLE_H