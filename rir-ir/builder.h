#ifndef RIR_BUILDER
# define RIR_BUILDER
# include "./nodes/prog.h"
# include "./nodes/function.h"
# include "./nodes/block.h"

static prog        *current_prog;
static function    *current_function;
static block       *current_block;

static void builder_begin(prog *p) {
    current_prog = p;
}

static prog *builder_get_prog(void) {
    return current_prog;
} 

static void builder_begin_function(function *f) {
    current_function = f;
}

static void builder_begin_block(block *b) {
    current_block = b;
}

static void builder_end(void) {
    current_prog = 0;
}


#endif