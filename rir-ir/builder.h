#ifndef RIR_BUILDER
# define RIR_BUILDER
# include <rir.h>

////

static void builder_begin(prog *p);

static prog *builder_get_prog(void);
static void builder_end(void);
////

static void builder_begin_function(function *f);

static function *builder_get_function();

////

static void builder_begin_block(block *b);

static void builder_begin_instr(instr *i);

static block *builder_get_block(void);

#endif