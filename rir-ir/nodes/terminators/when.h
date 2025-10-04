#ifndef RIR_WHEN_H
# define RIR_WHEN_H
# include <rir.h>

typedef struct when 
{
    terminator  terminator;
    value       *cond;
    block       *t;
    block       *f;
} when;

static void *when_visit(when *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "when").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}

static void When(value *cond, block *t, block *f) {
    block *current = builder_get_block();
    block *next = block("next");
    builder_set_block(t);
    jump(next);
    builder_set_block(f);
    jump(next);
    builder_set_block(current);
    when *self = new(when, 
        .terminator = {
            .instr = {
                .node = {
                    .accept = (ir_node_method) &when_visit,
                    .type = "instr"
                },
                .type = "terminator",
            },
            .type = "when",
        },
        .cond = cond,
        .t=t,
        .f=f
    );
    builder_attach_instr(&self->terminator.instr); 
    builder_set_block(next);
}
# define when(a,b,c) When(a,b,c)

#endif // RIR_WHEN_H