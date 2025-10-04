#include "target.h"

static node_visitor visitor;

//////////////////////////////////////////////////

node_visitor *c_visitor = &visitor;

void setup_c_target(Targets *targets)
{
    visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on c_visitor

    Targets_emplace(targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .visitor = &visitor
    ));
}
