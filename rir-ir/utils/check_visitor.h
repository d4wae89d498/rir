#ifndef RIR_CHECK_VISITOR_H
# define RIR_CHECK_VISITOR_H
# include <rir.h>

// TODO: use an STC vector so that this lis would be extensible

static char *methods[] = {
    // pure abstracts 
    "expr",
    "inst",
    "terminator",

    // pieces
    "prog",
    "function",
    "block",

    // instrs
    "deref",
    "var",

    // exprs
    "ref",
    "intlit",
    "strlit",
    "call",
    "arg",
    "binop",
    "value",
    // "phi"
    // "unaryop",


    // terminators
    "jump",
    "ret",
    // "unreachable",
    0
};

static void ensure_visitor_completed(const char *name, node_visitor *vis)
{
    bool should_exit = false;
    int i = 0;
    while (methods[i]) {
        node_visitor_iter r = node_visitor_find(vis, methods[i]);
        if (!r.ref) {
            fprintf(stderr, "ERROR: method %s not implemented for visitor %s (%p)\n", methods[i], name, (void*)vis);
            should_exit = 1;
        }
        i += 1;
    }
    if (should_exit)
        exit(1);
}

#endif