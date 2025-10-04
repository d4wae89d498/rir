#ifndef RIR_JUMP_H
# define RIR_JUMP_H
# include <rir.h>

struct jump
{
    terminator  terminator;
    block       *dest;
};

static void *jump_visit(jump *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "jump").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}

static void Jump(block *dest) {
    jump *self = new(jump, 
        .terminator = {
            .type = "jump",
            .instr = {
                .node = {
                    .accept = (ir_node_method) &jump_visit,
                    .type = "instr"
                },
                .type = "terminator"
            }
        },
        .dest = dest
    );
    builder_attach_instr(&self->terminator.instr); 
}

# define jump(x) Jump(x)

#endif // RIR_jump_H