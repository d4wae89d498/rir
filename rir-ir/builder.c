#ifndef RIR_BUILDER_IMPL_H
# define RIR_BUILDER_IMPL_H
# include <rir.h>

static prog        *current_prog;
static function    *current_function;
static block       *current_block;

void builder_begin(prog *p) {
    current_prog = p;
}

prog *builder_get_prog(void) {
    return current_prog;
} 

void builder_end(void) {
    current_prog = 0;
}

////

void builder_begin_function(function *f) {
    current_function = f;
}

function *builder_get_function(void) {
    return current_function;
}

////

void builder_begin_block(block *b) {
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

void builder_attach_instr(instr *i) {
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

block *builder_get_block(void) {
    return current_block;
}

#endif