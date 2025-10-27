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
    block *current = builder_get_block();
    block *next = block("next");
    builder_set_block(t);
    jump(next);
    builder_set_block(f);
    jump(next);
    builder_set_block(current);
    when *self = new(when, 
        .terminator = terminator_impl(
            .accept = (ir_node_method) &when_visit,
            .type = "when",
        ),
        .cond = cond,
        .t = t,
        .f = f
    );
    builder_attach_instr(&self->terminator.instr); 
    builder_set_block(next);
    return self;
}
# define when(a,b,c) when_new(a,b,c)

#endif // RIR_WHEN_H