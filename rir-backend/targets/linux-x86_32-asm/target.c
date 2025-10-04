#include "target.h"

static node_visitor visitor;

/////////////////////////////////////////////////////////////////////////////

node_visitor *linux_x86_32_asm_visitor = &visitor;

void setup_linux_x86_32_asm_target(Targets *targets)
{
    visitor = node_visitor_init();

    Targets_emplace(targets, "linux-x86_32-asm", new(target, 
        .name = "linux-x86_32-asm",
        .descr = "Emit a gas compatible assembly file.",
        .visitor = &visitor
    ));
}