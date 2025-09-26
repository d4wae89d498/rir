#include <rir.h>
#ifndef RIR_C_TARGET_H
# define RIR_C_TARGET_H

static node_visitor *c_visitor;

static target_setup setup_c_target;

static void setup_c_target(Targets *targets)
{
    c_visitor = new(node_visitor, 0);
    *c_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on c_visitor

    Targets_emplace(targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .vis = c_visitor
    ));
}

#endif