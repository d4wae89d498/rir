#include "./target.h"

node_visitor *linux_x86_32_jit_visitor;

void setup_linux_x86_32_jit_target(Targets *targets)
{
    linux_x86_32_jit_visitor = new(node_visitor, 0);
    *linux_x86_32_jit_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on linux_x86_32_jit_visitor

    Targets_emplace(targets, "linux-x86_32-jit", new(target, 
        .name = "linux-x86_32-jit",
        .descr = "Just-in-time compile and execute on 32-bit Linux.",
        .vis = linux_x86_32_jit_visitor
    ));
}