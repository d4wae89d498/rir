#include <rir.h>
#ifndef RIR_CLONE_VIS_H
# define RIR_CLONE_VIS_H

typedef struct clone_ctx {
    ptrmap ptrmap;
} clone_ctx;

extern node_visitor *clone_visitor;
void setup_clone_visitor(void);

#endif // RIR_CLONE_VIS_H