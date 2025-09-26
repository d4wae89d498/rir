
#include <rir.h>
#ifndef RIR_INTERPRET_TARGET_H
# define RIR_INTERPRET_TARGET_H

typedef struct interpret_ctx {
    int depth;
} interpret_ctx;

static node_visitor *interpret_visitor;

static target_setup setup_interpret_target;

static void *
visit_interpret_prog(prog *self, interpret_ctx *ctx) 
{
    return 0;
}

static void setup_interpret_target(Targets *targets)
{
    interpret_visitor = new(node_visitor, 0);
    *interpret_visitor = node_visitor_init();

    node_visitor *vis = interpret_visitor;
    visitor_method(interpret_prog);

    Targets_emplace(targets, "interpret", new(target, 
        .name = "interpret",
        .descr = "Interpret .",
        .vis = interpret_visitor
    ));
}

#endif