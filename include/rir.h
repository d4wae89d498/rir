#ifndef RIR_H
# define RIR_H

// COMMON DEPS
# include <assert.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>

# define i_static 1 // for STC header only
# define STC_HAS_TYPEOF 0 // c99 
# include <sugar.h>

# include <stc/cstr.h>
# define T hmap, cstr, void*, (c_keypro)
# include <stc/hmap.h>

// IR

typedef struct terminator terminator;
typedef struct block block;
typedef struct instr instr;
static void builder_begin_block(block*);
static block* builder_get_block(void);

# include "./../rir-ir/nodes/prog.h"

# include "./../rir-ir/builder.h"

# include "./../rir-ir/nodes/block.h"

# include "./../rir-ir/nodes/function.h"

# include "./../rir-ir/nodes/value.h"
# include "./../rir-ir/nodes/var.h"

# include "./../rir-ir/nodes/expr.h"


# include "./../rir-ir/nodes/expressions/load.h"
# include "./../rir-ir/nodes/expressions/store.h"
# include "./../rir-ir/nodes/expressions/ref.h"
# include "./../rir-ir/nodes/expressions/deref.h"

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

# include "./../rir-ir/visitors/print.h"

// BACKEND
// TODO

// PARSER
// TODO

# include "./../rir-ir/builder.impl.h"

#endif // RIR_H