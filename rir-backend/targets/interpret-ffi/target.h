
#ifndef RIR_INTERPRET_FFI_TARGET_H
# define RIR_INTERPRET_FFI_TARGET_H
# include <rir.h>

static node_visitor *interpret_ffi_visitor;

static void _setup_interpret_ffi_target(Targets *targets)
{
    interpret_ffi_visitor = new(node_visitor, 0);
    *interpret_ffi_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on interpret_ffi_visitor

    Targets_emplace(targets, "interpret-ffi", new(target, 
        .name = "interpret-ffi",
        .descr = "Run the IR directly using an interpreter using libffi.",
        .vis = interpret_ffi_visitor
    ));
}

target_setup setup_interpret_ffi_target = &_setup_interpret_ffi_target;

#endif