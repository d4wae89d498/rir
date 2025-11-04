#ifndef RIR_WHEN_H
# define RIR_WHEN_H
# include <rir.h>

struct when {
    terminator  terminator;
    value       *cond;
    block       *t;
    block       *f;
};

visitable(node_visitor, node, when, &self->terminator.impl)

static when *when_new(value *cond, block *t, block *f) {
    return new(when, 
        .terminator = terminator_impl(
            .accept = (ir_node_method) &when_visit,
            .type = "when",
        ),
        .cond = cond,
        .t = t,
        .f = f
    );
}

static when* When(value *cond, block *t, block *f) {
    when *self = when_new(cond, t, f);
    block *current = builder_get_block();
    block *next = block(0);
    builder_set_block(self->t);
    jump(next);
    builder_set_block(self->f);
    jump(next);
    builder_set_block(current);
    builder_attach_instr(&self->terminator.instr); 
    builder_set_block(next);
    return self;
}

# define when(a,b,c) When(a,b,c)

#endif // RIR_WHEN_H