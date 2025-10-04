#ifndef RIR_FUNCTION_H
# define RIR_FUNCTION_H
# include <rir.h>

struct function {
    node        node;
    const char  *name;
    block       *start;
    block       *end;
};

///////

# include "prog.h"

static void *function_visit(function *self, node_visitor *vis, void *ctx) {
    printf("-- %s start %p\n", self->name, (void*)self->start);

    return node_visitor_find(vis, "function").ref->second(
        &self->node,
        ctx
    );
}

static function *Function(const char *name) {
    function *out = new(function, 
         .node = {
            .accept = (ir_node_method) &function_visit,
            .type = "function"
        },
        .name = name,
    );
    
    builder_begin_function(out);

    prog *current_prog = builder_get_prog();
    functions_emplace(&(current_prog->functions), name, out);
    block(0);
    return 0;
}

# define function(name) Function(name);

#endif // RIR_FUNCTION_H