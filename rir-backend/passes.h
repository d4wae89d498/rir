#ifndef RIR_PASSES_H
# define RIR_PASSES_H
# include <rir.h>

typedef struct pass {
    char *name;
    const char *desc;
    node_visitor *visitor;
//    struct pass **deps;
} pass;

# define T Passes, cstr, pass*, (c_keypro)
# include <stc/hmap.h>
typedef void (pass_setup)(Passes*);

/////////////////////

#include "passes/ssa/pass.h"

/////////////////////

static Passes passes;
static void setup_passes(void)
{
    setup_ssa(&passes);
}

#endif