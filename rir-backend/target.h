#ifndef RIR_TARGET_H
# define RIR_TARGET_H
# include <rir.h>


/* Public API */
typedef struct target {
    const char      *name;
    const char      *descr;
    node_visitor    *vis; 
} target;

# define T Targets, cstr, target*, (c_keypro)
# include <stc/hmap.h>
typedef void (*target_setup)(Targets*);
# define visitor_method(W) \
    node_visitor_emplace(print_visitor, #W, (ir_visitor_method)& (visit_ ## W));


# include "./targets/print/target.h"
# include "./targets/c/target.h"
# include "./targets/interpret-ffi/target.h"
# include "./targets/linux-x86_32-asm/target.h"
# include "./targets/linux-x86_32-elf/target.h"
# include "./targets/linux-x86_32-jit/target.h"

/* Setup standard targets */
Targets targets;
static void setup_targets()
{
    setup_print_target(&targets);
    setup_c_target(&targets);
    setup_interpret_ffi_target(&targets);
    setup_linux_x86_32_asm_target(&targets);
    setup_linux_x86_32_jit_target(&targets);
    setup_linux_x86_32_elf_target(&targets);
}

#endif