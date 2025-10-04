#include "target.h"
#include "rir.h"

static node_visitor visitor;

/////////////////////////////////////////////////////////////////////////////

node_visitor *linux_x86_32_elf_visitor = &visitor;

void setup_linux_x86_32_elf_target(Targets *targets)
{
    visitor = node_visitor_init();

    // todo: implement me...

    Targets_emplace(targets, "linux-x86_32-elf", new(target, 
        .name = "linux-x86_32-elf",
        .descr = "Produce a 32-bit Linux ELF object file named according to what follows the colon.",
        .visitor = &visitor
    ));
}