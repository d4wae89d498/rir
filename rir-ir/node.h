#ifndef RIR_NODE
# define RIR_NODE
# include <rir.h>

# define node_base       \
    void* (*accept)();

typedef struct node {
    node_base
} node;

#endif