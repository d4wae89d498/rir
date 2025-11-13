#include <rir.h>
#ifndef RIR_PARSER_H
# define RIR_PARSER_H
# include <bpc.h>
# define T nodestack, node*
# include <stc/stack.h>

typedef struct parser_ctx 
{
    size_t      match_length;
    prog        *prog;
    cstrstack   csstack;
    strstack    sstack;
    nodestack   nstack;
    const char  *src;
} parser_ctx;

extern parser_ctx *std_parser_ctx;

void parse_str(const char *);
void parse_file(FILE*);

// === top-level ===

#define prog_rule           rule(prog_parser)
extern bpc_parser *prog_parser;

#define func_rule           rule(func_parser)
extern bpc_parser *func_parser;

// === statements ===

#define stmt_rule           rule(stmt_parser)
extern bpc_parser *stmt_parser;

#define stmt_block_rule     rule(stmt_block_parser)
extern bpc_parser *stmt_block_parser;

#define assign_rule         rule(assign_parser)
extern bpc_parser *assign_parser;

#define ret_rule            rule(ret_parser)
extern bpc_parser *ret_parser;

#define if_rule             rule(if_parser)
extern bpc_parser *if_parser;

#define while_rule          rule(while_parser)
extern bpc_parser *while_parser;

#define for_rule            rule(for_parser)
extern bpc_parser *for_parser;

// === expressions ===

#define expr_rule           rule(expr_parser)
extern bpc_parser *expr_parser;

#define cond_expr_rule      rule(cond_expr_parser)
extern bpc_parser *cond_expr_parser;

#define or_expr_rule        rule(or_expr_parser)
extern bpc_parser *or_expr_parser;

#define and_expr_rule       rule(and_expr_parser)
extern bpc_parser *and_expr_parser;

#define eq_expr_rule        rule(eq_expr_parser)
extern bpc_parser *eq_expr_parser;

#define rel_expr_rule       rule(rel_expr_parser)
extern bpc_parser *rel_expr_parser;

#define add_expr_rule       rule(add_expr_parser)
extern bpc_parser *add_expr_parser;

#define mul_expr_rule       rule(mul_expr_parser)
extern bpc_parser *mul_expr_parser;

#define unary_expr_rule     rule(unary_expr_parser)
extern bpc_parser *unary_expr_parser;

#define unary_op_rule       rule(unary_op_parser)
extern bpc_parser *unary_op_parser;

#define postfix_expr_rule   rule(postfix_expr_parser)
extern bpc_parser *postfix_expr_parser;

#define postfix_suffix_rule rule(postfix_suffix_parser)
extern bpc_parser *postfix_suffix_parser;

#define primary_expr_rule   rule(primary_expr_parser)
extern bpc_parser *primary_expr_parser;

#define arg_list_rule       rule(arg_list_parser)
extern bpc_parser *arg_list_parser;

// === terminals ===

#define id_rule             rule(id_parser)
extern bpc_parser *id_parser;

#define intlit_rule          rule(intlit_parser)
extern bpc_parser *intlit_parser;

#define strlit_rule         rule(strlit_parser)
extern bpc_parser *strlit_parser;


#endif