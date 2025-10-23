#ifndef RIR_PARSER_H
# define RIR_PARSER_H
# include <rir.h>
# include <bpc.h>

void parse_str(const char *);
void parse_file(FILE*);

#define prog_rule        rule(prog_parser)
extern bpc_parser *prog_parser;

#define id_rule          rule(id_parser)
extern bpc_parser *id_parser;

#define stmt_block_rule  rule(stmt_block_parser)
extern bpc_parser *stmt_block_parser;

#define func_rule        rule(func_parser)
extern bpc_parser *func_parser;

#define exp_rule         rule(expr_parser)
extern bpc_parser *expr_parser;

#define ret_rule         rule(ret_parser)
extern bpc_parser *ret_parser;

#define if_rule          rule(if_parser)
extern bpc_parser *if_parser;

#define while_rule       rule(while_parser)
extern bpc_parser *while_parser;

#define for_rule         rule(for_parser)
extern bpc_parser *for_parser;

#define binop_rule       rule(binop_parser)
extern bpc_parser *binop_parser;

#define unaryop_rule     rule(unaryop_parser)
extern bpc_parser *unaryop_parser;

#define intlit_rule      rule(intlit_parser)
extern bpc_parser *intlit_parser;

#define strlit_rule      rule(strlit_parser)
extern bpc_parser *strlit_parser;


#endif