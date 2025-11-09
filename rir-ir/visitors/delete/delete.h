
#include <rir.h>
#ifndef RIR_DELETE_VIS_H
# define RIR_DELETE_VIS_H

typedef struct delete_visitor_ctx {
    ptrset ptrset;
} delete_visitor_ctx;

extern node_visitor *delete_visitor;

void delete_visitor_flush(delete_visitor_ctx *ctx);
void setup_delete_visitor(void);

#endif // RIR_DELETE_VIS_H