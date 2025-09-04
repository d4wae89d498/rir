
#ifndef RIR_C_TARGET_H
# define RIR_C_TARGET_H
# include <rir.h>

static node_visitor *c_visitor;

static void _setup_c_target(Targets *targets)
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

target_setup setup_c_target = &_setup_c_target;

#endif