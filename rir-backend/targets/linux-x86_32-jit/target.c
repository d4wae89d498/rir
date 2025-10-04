#include "./target.h"

static node_visitor visitor;

/////////////////////////////////////////////////////////////////////////////

node_visitor *linux_x86_32_jit_visitor = &visitor;

void setup_linux_x86_32_jit_target(Targets *targets)
{
    visitor = node_visitor_init();

    // todo: implement me...

    Targets_emplace(targets, "linux-x86_32-jit", new(target, 
        .name = "linux-x86_32-jit",
        .descr = "Just-in-time compile and execute on 32-bit Linux.",
        .visitor = &visitor
    ));
}