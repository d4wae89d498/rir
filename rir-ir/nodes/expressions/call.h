#ifndef RIR_CALL_H
# define RIR_CALL_H
# include <rir.h>

struct  call {
    expr        expr;
    value       *fp;
    value       **args;
    int         arg_count;
};

visitable(node_visitor, node, call, self)

static call *call_new(value *addr, ...) {
    call *self = new(call,
        .expr = expr_impl(
            .accept = (node_method) &call_visit,
            .type = "call"
        ),
        .fp = addr,
        .args = NULL,
        .arg_count = 0
    );

    va_list ap;
    va_start(ap, addr);

    // First, count arguments
    int count = 0;
    value *v;
    va_list ap_copy;
    va_copy(ap_copy, ap);
    while ((v = va_arg(ap_copy, value *)) != 0) {
        count++;
    }
    va_end(ap_copy);

    // Allocate args array
    self->args = malloc(sizeof(value *) * count);
    self->arg_count = count;

    // Fill args array
    int i = 0;
    while ((v = va_arg(ap, value *)) != 0) {
        self->args[i++] = v;
    }

    va_end(ap);
    return self;
}

# define call(...) value(&call_new(__VA_ARGS__, 0)->expr)

#endif // RIR_CALL_H