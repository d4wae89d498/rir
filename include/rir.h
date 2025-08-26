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
# define T StrPtrMap, cstr, void*, (c_keypro)
# include <stc/hmap.h>

// IR
# include "./../rir-ir/builder.h"

# include "./../rir-ir/nodes/value.h"
# include "./../rir-ir/nodes/var.h"

# include "./../rir-ir/nodes/expressions/load.h"
# include "./../rir-ir/nodes/expressions/store.h"
# include "./../rir-ir/nodes/expressions/phi.h"
# include "./../rir-ir/nodes/expressions/arg.h"
# include "./../rir-ir/nodes/expressions/binop.h"
# include "./../rir-ir/nodes/expressions/call.h"
# include "./../rir-ir/nodes/expressions/unaryop.h"
# include "./../rir-ir/nodes/expressions/resolve.h"
# include "./../rir-ir/nodes/expressions/strlit.h"
// BACKEND
// TODO

// PARSER
// TODO

#endif // RIR_H