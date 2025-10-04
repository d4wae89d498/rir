#include "target.h"

static node_visitor visitor;

static void *visit_interpret_prog(prog *self, interpret_ctx *ctx) 
{
    return 0;
}

//////////////////////////////////////////////////////

node_visitor *interpret_visitor = &visitor;

void setup_interpret_target(Targets *targets)
{
    visitor = node_visitor_init();

    visitor_method(interpret_prog);

    Targets_emplace(targets, "interpret", new(target, 
        .name = "interpret",
        .descr = "Interpret .",
        .visitor = &visitor
    ));
}