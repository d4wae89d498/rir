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
    when *self = new(when, 
        .terminator = {
            .type = "when",
            .instr = {
                .type = "terminator",
                .node = {
                    .accept = (ir_node_method) &when_visit
                }
            }
        },
        .cond = cond,
        .t=t,
        .f=f
    );
    terminator(&self->terminator);
}
# define when(a,b,c) When(a,b,c)

#endif // RIR_WHEN_H