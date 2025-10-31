#ifndef RIR_IR_H
# define RIR_IR_H
#include <rir.h>

///////////////////////////////////////////////////
/////// NODES /////////////////////////////////////
// TODO: find why clangd report a false positive if struct node is in a separat-
// ed header
struct node {
    ir_node_method accept;
    const char *type;
};
//# include "./../rir-ir/node.h"

# include "./../rir-ir/builder.h"

# include "./../rir-ir/nodes/prog.h"
# include "./../rir-ir/nodes/block.h"
# include "./../rir-ir/nodes/function.h"

# include "./../rir-ir/nodes/instr.h"
# include "./../rir-ir/nodes/expr.h"
# include "./../rir-ir/nodes/value.h"
# include "./../rir-ir/nodes/var.h"

# include "./../rir-ir/nodes/var/load.h"
# include "./../rir-ir/nodes/var/store.h"
# include "./../rir-ir/nodes/var/ref.h"
# include "./../rir-ir/nodes/var/deref.h"

# include "./../rir-ir/nodes/expressions/phi.h"
# include "./../rir-ir/nodes/expressions/arg.h"
# include "./../rir-ir/nodes/expressions/binop.h"
# include "./../rir-ir/nodes/expressions/call.h"
# include "./../rir-ir/nodes/expressions/unaryop.h"
# include "./../rir-ir/nodes/expressions/resolve.h"
# include "./../rir-ir/nodes/expressions/strlit.h"
# include "./../rir-ir/nodes/expressions/intlit.h"

# include "./../rir-ir/nodes/terminator.h"
# include "./../rir-ir/nodes/terminators/jump.h"
# include "./../rir-ir/nodes/terminators/ret.h"
# include "./../rir-ir/nodes/terminators/when.h"

///////////////////////////////////////////////////
/////// UTILS /////////////////////////////////////

# include "utils/check_visitor.h"

///////////////////////////////////////////////////
/////// VISITOR ///////////////////////////////////

# include "visitors.h"

#endif