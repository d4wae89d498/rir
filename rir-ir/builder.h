#ifndef RIR_BUILDER
# define RIR_BUILDER
# include <rir.h>

//// Prog builder

void builder_begin(prog *p);
prog *builder_get_prog(void);
void builder_end(void);

//// Function builder

void builder_begin_function(function *f);
function *builder_get_function(void);

//// Block / instr builder

void builder_begin_block(block *b);
void builder_begin_instr(instr *i);
block *builder_get_block(void);

#endif