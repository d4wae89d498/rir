#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

struct ret
{
    terminator  terminator;
    value       *value;
};

static void *ret_visit(ret *self, node_visitor *vis, void *ctx) {
    trace();
    return (node_visitor_find(vis,  "ret").ref)->second(
        &self->terminator.instr.node,
        ctx
    );
}
    

void Ret(value *value) {
    ret *self = new(ret, 
        .terminator = {
            .type = "ret",
            .instr = {
                .type = "terminator",
                .node = {
                    .accept = (ir_node_method) &ret_visit
                }
            }
        },
        .value = value
    );
    terminator(&self->terminator);
}

# define ret(x) Ret(x)

#endif // RIR_RET_H