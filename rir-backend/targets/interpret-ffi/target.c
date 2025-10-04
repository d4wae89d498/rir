#include "target.h"

static node_visitor visitor;

node_visitor *interpret_ffi_visitor = &visitor;

void setup_interpret_ffi_target(Targets *targets)
{
    visitor = node_visitor_init();

    Targets_emplace(targets, "interpret-ffi", new(target, 
        .name = "interpret-ffi",
        .descr = "Export IR functions as C-ABI compatible functions using libFFI , such functions are then interpreted like 'interpret' target.",
        .visitor = &visitor
    ));
}