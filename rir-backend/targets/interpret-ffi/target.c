#include "target.h"

node_visitor *interpret_ffi_visitor;

void setup_interpret_ffi_target(Targets *targets)
{
    interpret_ffi_visitor = new(node_visitor, 0);
    *interpret_ffi_visitor = node_visitor_init();

    // todo: implemement visitor by using emplace on interpret_ffi_visitor

    Targets_emplace(targets, "interpret-ffi", new(target, 
        .name = "interpret-ffi",
        .descr = "Export IR functions as C-ABI compatible functions using libFFI , such functions are then interpreted like 'interpret' target.",
        .vis = interpret_ffi_visitor
    ));
}