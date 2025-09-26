
#include <rir.h>
#ifndef RIR_INTERPRET_FFI_TARGET_H
# define RIR_INTERPRET_FFI_TARGET_H

typedef struct interpret_ffi_ctx {
    int depth;
} interpret_ffi_ctx;

extern node_visitor *interpret_ffi_visitor;

extern target_setup setup_interpret_ffi_target;

#endif