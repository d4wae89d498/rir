#ifndef RIR_NODE
# define RIR_NODE
# include <rir.h>

typedef struct node node;

typedef void *(*ir_visitor_method )(node *, void*);
typedef void *(*ir_node_method )(node *, hmap *, void*);


# define node_base       \
    ir_node_method accept;

struct node {
    node_base
};

#endif