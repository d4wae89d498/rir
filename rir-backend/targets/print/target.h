
#include <rir.h>
#ifndef RIR_PRINT_H
# define RIR_PRINT_H

typedef struct target_ctx {
    int depth;
} target_ctx;

extern node_visitor *print_visitor;

extern target_setup setup_print_target;

//void setup_print_target(Targets *targets);

#endif