
#include <rir.h>
#ifndef RIR_PRINT_VIS_H
# define RIR_PRINT_VIS_H

typedef struct print_visitor_ctx {
    FILE*   ostream;
    int     depth;
} print_visitor_ctx;

extern node_visitor *print_visitor;
void setup_print_visitor(void);

#endif // RIR_PRINT_VIS_H