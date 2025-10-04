#include "pass.h"


static node_visitor visitor;

/////////////////////////////////////////////////////////

void setup_ssa(Passes *passes)
{
    Passes_emplace(passes, "ssa", new(pass, 
        .name = "ssa",
        .desc = "Flatify vars into REG or ALLOCA calls according its use in the code.",
//        .deps = (pass*[]){0, 0},
        .visitor = &visitor
    ));
}

node_visitor *ssa_visitor = &visitor;
