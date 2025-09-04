#ifndef RIR_TARGET_H
# define RIR_TARGET_H
# include <rir.h>

typedef struct target {
    const char      *name;
    const char      *descr;
    node_visitor    *vis; 
} target;

# define T Targets, cstr, target*, (c_keypro)
# include <stc/hmap.h>


Targets targets;

# include "./targets/print/print.h"

static void setup_targets()
{
    setup_print_target();
}

// todo : create a tarhet map and provide a primitive to make new target

#endif