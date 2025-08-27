#ifndef RIR_FUNCTION_H
# define RIR_FUNCTION_H
# include <rir.h>

typedef struct function {
    const char  *name;
    block       *start;
} function;

static void builder_begin_function(function*);

static prog *builder_get_prog(void);

static function *Function(const char *name) {
    function *out = new(function, .name = name);
    
    builder_begin_function(out);

    prog *current_prog = builder_get_prog();
    StrPtrMap_emplace(&(current_prog->functions), name, out);

    return 0;
}

# define function(name) Function(name);

#endif // RIR_FUNCTION_H