#ifndef STCUTILS_H
# define STCUTILS_H
# include <stc/cstr.h>
# define T ptrmap, void*, void*
# include <stc/hmap.h>
# define T strstack, const char*
# include <stc/stack.h>
# define visitable(visitor, node, type, access)  \
static void * type ##  _visit(node *f, visitor *vis, void *ctx) {\
    type *self = (type*)f;\
    return (visitor ## _find(vis, #type ).ref)->second(\
        (node*)(access), \
        ctx\
    );\
}

#endif