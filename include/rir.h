#ifndef RIR_H
# define RIR_H

// libc/system
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
# include <getopt.h>

// third party
# include <stc/cstr.h>
# define T hmap, cstr, void*, (c_keypro)
# include <stc/hmap.h>
# include <sugar.h>


// IR

typedef struct node         node;

typedef struct prog         prog;
typedef struct function     function;
typedef struct block        block;

typedef struct instr        instr;
typedef struct expr         expr;  // a node 

// instrs
typedef struct value        value;
typedef struct var          var;
typedef struct terminator   terminator;

// exprs
typedef struct binop        binop;
typedef struct unaryop      unaryop;
typedef struct call         call;
typedef struct strlit       strlit;
typedef struct intlit       intlit;
typedef struct store        store;
typedef struct load         load;
typedef struct ref          ref;
typedef struct deref        deref;

// terminators 
typedef struct ret          ret;
typedef struct jump         jump;

# define T functions, cstr, function*, (c_keypro)
# include <stc/hmap.h>

static void builder_begin_block(block*);
static block* builder_get_block(void);



typedef void *(*ir_visitor_method )(node *, void*);

# define T node_visitor, cstr, ir_visitor_method, (c_keypro)
# include <stc/hmap.h>

typedef void *(*ir_node_method )(node *, node_visitor*, void*);



# include "./../rir-ir/node.h"

# include "./../rir-ir/nodes/expr.h"

# include "./../rir-ir/nodes/prog.h"

# include "./../rir-ir/builder.h"

# include "./../rir-ir/nodes/block.h"

# include "./../rir-ir/nodes/function.h"

# include "./../rir-ir/nodes/instr.h"


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

// BACKEND
// TODO

// PARSER
// TODO

# include "./../rir-ir/builder.impl.h"




# include "./../rir-backend/target.h"


#endif // RIR_H