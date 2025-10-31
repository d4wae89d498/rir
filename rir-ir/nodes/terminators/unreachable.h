#ifndef RIR_UNREACHABLE_H
# define RIR_UNREACHABLE_H
# include <rir.h>

struct unreachable {
    terminator terminator;
};

visitable(node_visitor, node, unreachable, &self->terminator.impl)

static unreachable *unreachable_new(void) {
    return new(unreachable, 
        .terminator = terminator_impl(
            .accept = &unreachable_visit,
            .type = "unreachable",
        ),
    );
}

#undef unreachable // maybe def in __stddef_unreachable... todo: checkwhy or rename..
#define unreachable() builder_attach_instr(&unreachable_new()->terminator.instr); 

#endif // RIR_UNREACHABLE_H