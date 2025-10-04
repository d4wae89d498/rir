
#include <rir.h>
#ifndef RIR_INTERPRET_TARGET_H
# define RIR_INTERPRET_TARGET_H

typedef struct interpret_ctx {
    int depth;
} interpret_ctx;

extern node_visitor *interpret_visitor;

extern target_setup setup_interpret_target;

#endif