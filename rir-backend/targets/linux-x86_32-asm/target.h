
#ifndef RIR_LINUX_X86_32_ASM_TARGET_H
# define RIR_LINUX_X86_32_ASM_TARGET_H
# include <rir.h>

static node_visitor *linux_x86_32_asm_visitor;

static void _setup_linux_x86_32_asm_target(Targets *targets)
{
    linux_x86_32_asm_visitor = new(node_visitor, 0);
    *linux_x86_32_asm_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on linux_x86_32_asm_visitor

    Targets_emplace(targets, "linux-x86_32-asm", new(target, 
        .name = "linux-x86_32-asm",
        .descr = "Emit a gas compatible assembly file.",
        .vis = linux_x86_32_asm_visitor
    ));
}

target_setup setup_linux_x86_32_asm_target = &_setup_linux_x86_32_asm_target;

#endif