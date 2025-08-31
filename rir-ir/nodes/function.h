#ifndef RIR_FUNCTION_H
# define RIR_FUNCTION_H
# include <rir.h>

typedef struct function {
    node        node;
    const char  *name;
    block       *start;
    block       *end;
} function;

static void builder_begin_function(function*);
static prog *builder_get_prog(void);

static void *function_visit(function *self, node_visitor *vis, void *ctx) {
    printf("-- %s start %p\n", self->name, (void*)self->start);

    node *start_node = &(self->start->node);
    start_node->accept(start_node, vis, ctx);

    return 0;
}

static function *Function(const char *name) {
    function *out = new(function, 
         .node = {
            .accept = (ir_node_method) &function_visit
        },
        .name = name,
    );
    
    builder_begin_function(out);

    prog *current_prog = builder_get_prog();
    hmap_emplace(&(current_prog->functions), name, out);

    return 0;
}

# define function(name) Function(name);

#endif // RIR_FUNCTION_H