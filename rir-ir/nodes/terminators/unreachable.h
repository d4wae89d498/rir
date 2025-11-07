#ifndef RIR_UNREACHABLE_H
# define RIR_UNREACHABLE_H
# include <rir.h>

struct  unreachable {
    terminator terminator;
};

visitable(node_visitor, node, unreachable, self)

static unreachable *unreachable_new(void) {
    return new(unreachable, 
        .terminator = terminator_impl(
            .accept = &unreachable_visit,
            .type = "unreachable",
        ),
    );
}

static unreachable *Unreachable(void) {
    unreachable *self = unreachable_new();
    builder_attach_instr(&self->terminator.instr); 
    return self;
}

#undef unreachable // maybe def in __stddef_unreachable... todo: checkwhy or rename..
#define unreachable() Unreachable()

#endif // RIR_UNREACHABLE_H