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
        (node*)(access),\
        vis,\
        ctx\
    );\
}

static void *ptrmap_hit(ptrmap *map, void *ptr) {
    ptrmap_iter arg_at_i = ptrmap_find(map, ptr);
    if (!arg_at_i.ref) {
        return 0;
    }
    return arg_at_i.ref->second;
}

#endif