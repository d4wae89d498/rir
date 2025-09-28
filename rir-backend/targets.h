#ifndef RIR_TARGETS_H
# define RIR_TARGETS_H
# include <rir.h>


/* Public API */
typedef struct target {
    const char      *name;
    const char      *descr;
    node_visitor    *vis; 
} target;

# define T Targets, cstr, target*, (c_keypro)
# include <stc/hmap.h>
typedef void (target_setup)(Targets*);
# define visitor_method(W) \
    node_visitor_emplace(vis, #W, (ir_visitor_method)& (visit_ ## W));


# include "./targets/print/target.h"
# include "./targets/c/target.h"
# include "./targets/interpret/target.h"
# include "./targets/interpret-ffi/target.h"
# include "./targets/linux-x86_32-asm/target.h"
# include "./targets/linux-x86_32-elf/target.h"
# include "./targets/linux-x86_32-jit/target.h"

//extern target_setup setup_print_target;
//void setup_print_target (Targets*);
/* Setup standard targets */
static Targets targets;
static void setup_targets(void)
{
    setup_print_target(&targets);
    setup_c_target(&targets);
    setup_interpret_target(&targets);
    setup_interpret_ffi_target(&targets);
    setup_linux_x86_32_asm_target(&targets);
    setup_linux_x86_32_jit_target(&targets);
    setup_linux_x86_32_elf_target(&targets);
}

#endif