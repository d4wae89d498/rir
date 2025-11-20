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
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <time.h>

// third party
# include <stcutils.h>
# include <sugar.h>
# include <diag.h>

typedef struct node         node;

struct node_visitor;

typedef void *(*node_method )(struct node *, struct node_visitor*, void*);
# define T node_visitor, cstr, node_method, (c_keypro)
# include <stc/hmap.h>
# define visitor_method(W) \
    node_visitor_put(&visitor, #W, (node_method)& (visit_ ## W));

struct node {
    node_method accept;
    const char *type;
};

////////////////////////////////////////////////////////////////////////////////
//////////////           IR             ////////////////////////////////////////

typedef struct prog         prog;
typedef struct function     function;
typedef struct block        block;

typedef struct instr        instr;
typedef struct expr         expr;  // a node 

// instrs
typedef struct value        value;
typedef struct var          var;
typedef struct deref        deref;
typedef struct terminator   terminator;

// exprs
typedef struct resolve      resolve;
typedef struct arg          arg;
typedef struct binop        binop;
typedef struct unaryop      unaryop;
typedef struct call         call;
typedef struct strlit       strlit;
typedef struct intlit       intlit;
typedef struct store        store;
typedef struct load         load;
typedef struct ref          ref;
typedef struct phi          phi;

// terminators 
typedef struct ret          ret;
typedef struct jump         jump;
typedef struct when         when;
typedef struct unreachable  unreachable;

# define T functions, cstr, function*, (c_keypro)
# include <stc/hmap.h>


# include "./../rir-ir/ir.h"


////////////////////////////////////////////////////////////////////////////////
//////////////           BACKEND             ///////////////////////////////////

# include "./../rir-backend/passes.h"
# include "./../rir-backend/targets.h"


////////////////////////////////////////////////////////////////////////////////
//////////////           PARSERS             ///////////////////////////////////

# include "./../rir-parser/parser.h"


////////////////////////////////////////////////////////////////////////////////
//////////////           SETUP         ////////////////////////////////////////

static void setup(void)
{
    TRACE;
    libdiag_setup_defaults();
    setup_passes();
    setup_targets();
    setup_visitors();
}

#endif // RIR_H
