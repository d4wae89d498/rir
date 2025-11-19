// prog
prog            : top_decl* ;

// top_decl
top_decl        : func_def
                | variable_decl ';'
                | 'extern' identifier_list ';'
                | ';'
                ;

// func_def
func_def        : 'export'? IDENTIFIER '(' identifier_list? ')' statement ;


// id_list
identifier_list : IDENTIFIER (',' IDENTIFIER)* ;


// var_decl
variable_decl   : 'static'? ('var' IDENTIFIER ('=' assignment_expr)?
                | 'const' IDENTIFIER '=' assignment_expr)
                ;

// stmt
statement       : labeled_stmt
                | expr_stmt
                | compound_stmt
                | if_stmt
                | while_stmt
                | for_stmt
                | jump_stmt
                | ';'
                ;

// block_item
block_item      : block_decl
                | statement
                ;

// block_decl
block_decl      : variable_decl ';'
                | ';'
                ;

// compound_stmt
compound_stmt   : '{' block_item* '}' ;

// labeled_stmt
labeled_stmt    : IDENTIFIER ':' statement
                ;

// jump_stmt
jump_stmt       : 'goto' IDENTIFIER ';'
                | 'return' expr? ';'
                | 'break' ';'
                | 'continue' ';'
                ;

// if_stmt
if_stmt         : 'if' '(' expr ')' statement ('else' statement)?
                ;

// while_stmt
while_stmt      : 'while' '(' expr ')' statement ;

// for_stmt
for_stmt        : 'for' '(' for_init expr? ';' expr? ')' statement ;

// for_init
for_init        : variable_decl
                | expr_stmt
                | ';'
                ;

// expr_stmt
expr_stmt       : expr? ';' ;

// const_expr
const_expr      : cond_expr ;

// expr
expr            : assignment_expr
                | expr ',' assignment_expr
                ;

// assignment_expr
assignment_expr : cond_expr
                | unary_expr assignment_op assignment_expr
                ;
// assignment_op
assignment_op   : '=' | '+=' | '-=' | '*=' | '/=' | '%=' ;

// cond_expr
cond_expr       : log_or_expr ('?' expr ':' cond_expr)?
                ;

// log_or_expr (or_expr)
log_or_expr     : log_and_expr ('||' log_and_expr)* ;

// log_and_expr (and_expr)
log_and_expr    : eq_expr ('&&' eq_expr)* ;

// eq_expr
eq_expr         : rel_expr (('==' | '!=') rel_expr)* ;

// rel_expr
rel_expr        : add_expr (('<' | '>' | '<=' | '>=') add_expr)* ;

// add_expr
add_expr        : mult_expr (('+' | '-') mult_expr)* ;

// mult_expr
mult_expr       : unary_expr (('*' | '/' | '%') unary_expr)* ;

// unary_expr
unary_expr      : postfix_expr
                | '++' unary_expr
                | '--' unary_expr
                | ('&' | '*' | '+' | '-' | '!') unary_expr
                ;

// postfix_expr
postfix_expr    : prim_expr postfix_suffix* ;

// postfix_suffix
postfix_suffix  : '[' expr ']'                      // lvalue
                | '(' arg_list? ')'                 // call
                | '.' IDENTIFIER                    // struct member
                | '++'
                | '--'
                ;

// prim_expr
prim_expr       : IDENTIFIER                        // rvalue
                | CONSTANT
                | STRING_LITERAL
                | '(' expr ')'
                ;

// arg_list
arg_list        : assignment_expr (',' assignment_expr)* ;