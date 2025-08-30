#ifndef RIR_FUNCTION_H
# define RIR_FUNCTION_H
# include <rir.h>

typedef struct function {
    node_base

    const char  *name;
    block       *start;
    block       *end;
} function;

static void builder_begin_function(function*);
static prog *builder_get_prog(void);

static void *function_visit(function *self, hmap *vis, void *ctx) {
    printf("-- %s start %p\n", self->name, (void*)self->start);
    self->start->accept((node*)self->start, vis, ctx);
    return 0;
}

static function *Function(const char *name) {
    function *out = new(function, 
        .name = name,
        .accept = (ir_node_method) &function_visit
    );
    
    builder_begin_function(out);

    prog *current_prog = builder_get_prog();
    hmap_emplace(&(current_prog->functions), name, out);

    return 0;
}

# define function(name) Function(name);

#endif // RIR_FUNCTION_H