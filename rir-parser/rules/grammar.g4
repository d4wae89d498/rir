/// Grammmaire ci-dessous pour reference seulement ! L'implémentation C fait fois

// prog
prog            : func* ;

// func
func            : IDENTIFIER '(' param_list? ')' compound_statement ;

// param_list
param_list      : IDENTIFIER (',' IDENTIFIER)* ;

// stmt
statement       : assignment_statement ';'
                | expression
                | compound_statement
                | if_statement
                | while_statement
                | for_statement
                | ';'
                ;

// stmt_block
compound_statement
                : '{' statement* '}' ;

// if
if_statement    : 'if' '(' expression ')' statement ('else' statement)?
                ;

// while
while_statement : 'while' '(' expression ')' statement ;

// for
for_statement   : 'for' '(' assign? ';' expression? ';' assign? ')' statement ;

// assign
assignment_statement
                : unary_expression '=' expression
                ;

// expr
expression      : conditional_expression ;

// cond_expr
conditional_expression
                : logical_or_expression ('?' expression ':' conditional_expression)? ;

// or_expr
logical_or_expression
                : logical_and_expression ('||' logical_and_expression)* ;

// and_expr
logical_and_expression
                : equality_expression ('&&' equality_expression)* ;

// eq_expr
equality_expression
                : relational_expression (('=' '=') | ('!' '=')) relational_expression)* ;

// rel_expr
relational_expression
                : additive_expression (('<' | '>' | '<=' | '>=') additive_expression)* ;

// add_expr
additive_expression
                : multiplicative_expression (('+' | '-') multiplicative_expression)* ;

// mult_expr
multiplicative_expression
                : unary_expression (('*' | '/' | '%') unary_expression)* ;

// unary_expr
unary_expression
                : postfix_expression
                | '++' unary_expression
                | '--' unary_expression
                |  ('&' | '*' | '+' | '-' | '!') unary_expression
                ;

// postfix_expr
postfix_expression
                : primary_expression postfix_suffix* ;


// postfix_suffix
postfix_suffix  : '[' expression ']'
                | '(' argument_expression_list? ')'
                | '++'
                | '--'
                ;

// primary_expr
primary_expression
                : IDENTIFIER
                | CONSTANT
                | STRING_LITERAL
                | '(' expression ')'
                ;

// arg_list
argument_expression_list            
                : expression (',' expression)* ;