#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

struct ret
{
    terminator  terminator;
    value       *value;
};

static void *ret_visit(ret *self, node_visitor *vis, void *ctx) {
    return (node_visitor_find(vis,  "ret").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}

static void Ret(value *value) {
    ret *self = new(ret, 
        .terminator = {
            .type = "ret",
            .instr = {
                .node = {
                    .accept = (ir_node_method) &ret_visit,
                    .type = "instr"
                },
                .type = "terminator",
            }
        },
        .value = value
    );
    builder_attach_instr(&self->terminator.instr); 
}

# define ret(x) Ret(x)

#endif // RIR_RET_H