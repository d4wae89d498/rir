#include <rir.h>

void setup_print_target(Targets *targets)
{
    TRACE;
    // register visitor
    Targets_emplace(targets, "print", new(target, 
        .name = "print",
        .descr = "Print the IR in a human readable format.",
        .visitor = print_visitor
    ));
}