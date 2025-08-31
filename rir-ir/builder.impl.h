#ifndef RIR_BUILDER_IMPL_H
# define RIR_BUILDER_IMPL_H
# include <rir.h>

prog        *current_prog;
function    *current_function;
block       *current_block;

static void builder_begin(prog *p) {
    current_prog = p;
}

static prog *builder_get_prog(void) {
    return current_prog;
} 

static void builder_end(void) {
    current_prog = 0;
}

////

static void builder_begin_function(function *f) {
    trace();
    current_function = f;
}

static function *builder_get_function() {
    return current_function;
}

////

static void builder_begin_block(block *b) {
    trace();
    current_block = b;
    // TODO: if (current_function == NULL) Error
    if (!current_function->start) {
        current_function->start = current_function->end = b;
    } else {
        current_function->end->next = b;
        current_function->end->prev = current_function->end;
    
        current_function->end = b;
    }
}

static void builder_begin_instr(instr *i) {
    trace();
    block *b = current_block;
    printf("instr for b->name = %s\n", b->name);
    // TODO: if (b == NULL) Error
    if (!b->start)
    {
        printf("first!\n");
        b->start = b->last =  i;
    }
    else
    {
        printf("pushed!\n");
        b->last->next = i;
        i->prev = b->last;
        b->last = i;

    }
}

static block *builder_get_block(void) {
    return current_block;
}

#endif