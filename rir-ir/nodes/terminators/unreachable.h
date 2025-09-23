#ifndef RIR_UNREACHABLE_H
# define RIR_UNREACHABLE_H
# include <rir.h>

typedef struct unreachable 
{
    terminator terminator;
} unreachable;

static void *unreachable_visit(ret *self, node_visitor *vis, void *ctx) {
    trace();
    return (node_visitor_find(vis,  "unreachable").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}

void Unreachable() {
    ret *self = new(ret, 
        .terminator = {
            .type = "unreachable",
            .instr = {
                .type = "terminator",
                .node = {
                    .accept = (ir_node_method) &unreachable_visit
                }
            }
        },
    );
    terminator(&self->terminator);
}
#undef unreachable // maybe def in __stddef_unreachable... todo: checkwhy or rename..
#define unreachable() Unreachable()

#endif // RIR_UNREACHABLE_H