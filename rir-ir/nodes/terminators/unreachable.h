#ifndef RIR_UNREACHABLE_H
# define RIR_UNREACHABLE_H
# include <rir.h>

typedef struct unreachable 
{
    terminator terminator;
} unreachable;

static void *unreachable_visit(ret *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "unreachable").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}

static void Unreachable() {
    ret *self = new(ret, 
        .terminator = {
            .instr = {
                .node = {
                    .accept = (ir_node_method) &unreachable_visit,
                    .type = "instr"
                },
                .type = "terminator",
            },
            .type = "unreachable",
        },
    );
    builder_attach_instr(&self->terminator.instr); 
}
#undef unreachable // maybe def in __stddef_unreachable... todo: checkwhy or rename..
#define unreachable() Unreachable()

#endif // RIR_UNREACHABLE_H