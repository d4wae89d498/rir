#ifndef RIR_FUNCTION_H
# define RIR_FUNCTION_H
# include <rir.h>

struct  function {
    node        node;
    const char  *name;
    block       *start;
    block       *end;
};

visitable(node_visitor, node, function, self)

static function *function_new(const char *name) {
    return new(function, 
         .node = {
            .accept = (node_method) &function_visit,
            .type = "function"
        },
        .name = name,
    );
}

static function *Function(const char *name) {
    function *out = function_new(name);
    builder_begin_function(out);
    prog *current_prog = builder_get_prog();
    functions_emplace(&(current_prog->functions), name, out);
    block();
    return out;
}

# define function(name) Function(name);

#endif // RIR_FUNCTION_H