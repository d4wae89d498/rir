#ifndef RIR_H
# define RIR_H

////////////////////////////////////////////////////////////////////////////////
//////////////           COMMON         ////////////////////////////////////////

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
# include <sugar.h>

// optinal: make test file easier
# if __STDC_VERSION__ >= 201112L
#  include <c11/fmt.h>
# endif


////////////////////////////////////////////////////////////////////////////////
//////////////           IR             ////////////////////////////////////////


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
typedef void *(*ir_visitor_method )(node *, void*);
# define T node_visitor, cstr, ir_visitor_method, (c_keypro)
# include <stc/hmap.h>
typedef void *(*ir_node_method )(node *, node_visitor*, void*);

# include "./../rir-ir/ir.h"


////////////////////////////////////////////////////////////////////////////////
//////////////           TARGETS             ///////////////////////////////////

# include "./../rir-backend/targets.h"


////////////////////////////////////////////////////////////////////////////////
//////////////           PARSERS             ///////////////////////////////////


// TODO



#endif // RIR_H
