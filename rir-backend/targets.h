#ifndef RIR_TARGETS_H
# define RIR_TARGETS_H
# include <rir.h>


/* Public API */
typedef struct target {
    const char      *name;
    const char      *descr;
    node_visitor    *visitor; 
} target;

# define T Targets, cstr, target*, (c_keypro)
# include <stc/hmap.h>
typedef void (target_setup)(Targets*);

/////////////////////

# include "./targets/print/target.h"
# include "./targets/c/target.h"
# include "./targets/interpret/target.h"
# include "./targets/interpret-ffi/target.h"
# include "./targets/linux-x86_32-asm/target.h"
# include "./targets/linux-x86_32-elf/target.h"
# include "./targets/linux-x86_32-jit/target.h"

/////////////////////

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