
#include <rir.h>
#ifndef RIR_PRINT_H
# define RIR_PRINT_H

typedef struct print_target_ctx {
    FILE*   ostream;
    int     depth;
} print_target_ctx;

extern node_visitor *print_visitor;

extern target_setup setup_print_target;

#endif