#include "target.h"

node_visitor *linux_x86_32_elf_visitor;

void setup_linux_x86_32_elf_target(Targets *targets)
{
    linux_x86_32_elf_visitor = new(node_visitor, 0);
    *linux_x86_32_elf_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on linux_x86_32_elf_visitor

    Targets_emplace(targets, "linux-x86_32-elf", new(target, 
        .name = "linux-x86_32-elf",
        .descr = "Produce a 32-bit Linux ELF object file named according to what follows the colon.",
        .vis = linux_x86_32_elf_visitor
    ));
}