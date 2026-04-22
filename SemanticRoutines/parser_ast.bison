%{
     #include <stdio.h>
     #include <stdlib.h>
     #include "ast.h"     

     struct stmt * parser_result;
     extern char *yytext;
     extern int yylex(void);
     
     int yyerror(char *s);
     
%}

%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_LPAREN
%token TOKEN_RPAREN
%token TOKEN_SEMI
%token TOKEN_ERROR

%token TOKEN_WRITE
%token TOKEN_IF
%token TOKEN_FOR
%token TOKEN_TRUE
%token TOKEN_VARIABLE
%token TOKEN_DIGIT
%token TOKEN_STR
%token TOKEN_LBRACE
%token TOKEN_RBRACE
%token TOKEN_SEMICOLON
%token TOKEN_EQUAL
%token TOKEN_SMALLER
%token TOKEN_LARGER
%token TOKEN_HASH
%token TOKEN_EXCLAIM

%union {
     struct decl *decl;
     struct stmt *stmt;
     struct expr *expr;
     struct type *type;
     char *name;
};
 
%type <stmt> program stmt_list stmt simple_stmt if_stmt statement
%type <expr> comparison expr term factor
%type <decl> decl

%type <type> type
%token <type> TOKEN_INT TOKEN_STRING
%type <name> name
%token <name> TOKEN_NAME 

%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MUL TOKEN_DIV

%%
program : stmt_list		{ parser_result = $1; }
	;

stmt_list : stmt_list stmt	{ $2->next = $1; $$ = $2; } 
	| stmt			{ $$ = $1; }
	;

stmt : simple_stmt		{ $$ = $1; }
	| if_stmt		{ $$ = $1; }
	;

simple_stmt : decl TOKEN_SEMICOLON		{ $$ = stmt_create(STMT_DECL, $1, 0, 0, 0, 0, 0, 0); }
		| statement TOKEN_SEMICOLON 	{ $$ = $1; }
		;

if_stmt : TOKEN_IF TOKEN_LPAREN expr TOKEN_RPAREN TOKEN_LBRACE stmt_list TOKEN_RBRACE	{ $$ = stmt_create(STMT_IF_ELSE, 0, 0, $3, 0, $6, 0, 0); }
	;

expr : factor comparison factor	{ $2->left = $1; $2->right = $3; $$ = $2; }
	| factor		{ $$ = $1; }
	| TOKEN_TRUE		{ $$ = expr_create_integer_literal(1);}	
	;

comparison : TOKEN_EQUAL TOKEN_EQUAL			{ $$ = expr_create(EXPR_EQ, 0, 0); }
			| TOKEN_SMALLER			{ $$ = expr_create(EXPR_LT, 0, 0); }
			| TOKEN_LARGER			{ $$ = expr_create(EXPR_GT, 0, 0); }
			| TOKEN_SMALLER TOKEN_EQUAL	{ $$ = expr_create(EXPR_LE, 0, 0); }
			| TOKEN_LARGER TOKEN_EQUAL	{ $$ = expr_create(EXPR_GE, 0, 0); }
			| TOKEN_EXCLAIM TOKEN_EQUAL	{ $$ = expr_create(EXPR_NE, 0, 0); }
			;


factor : name				{ $$ = expr_create_name($1); }
	| TOKEN_DIGIT 			{ $$ = expr_create_integer_literal(atoi(yytext)); }
	| factor TOKEN_PLUS factor	{ $$ = expr_create(EXPR_ADD, $1, $3); }
	| factor TOKEN_MINUS factor	{ $$ = expr_create(EXPR_SUB, $1, $3); }
	| factor TOKEN_MUL factor	{ $$ = expr_create(EXPR_MUL, $1, $3); }
	| factor TOKEN_DIV factor	{ $$ = expr_create(EXPR_DIV, $1, $3); }
	;


term : TOKEN_STR			{ $$ = expr_create_string_literal(strdup(yytext)); }
	| TOKEN_STR TOKEN_PLUS term	{ $$ = expr_create(EXPR_ADD, expr_create_string_literal(strdup(yytext)), $3); }
	| name				{ $$ = expr_create_name($1); }
	| name TOKEN_PLUS term		{ $$ = expr_create(EXPR_ADD, expr_create_name($1), $3); }
	;

decl : type name TOKEN_EQUAL TOKEN_DIGIT	{ $$ = decl_create($2, $1, expr_create_integer_literal(atoi(yytext)), 0, 0); }
	| type name TOKEN_EQUAL TOKEN_STR	{ $$ = decl_create($2, $1, expr_create_string_literal(strdup(yytext)), 0, 0); }
	;

statement : TOKEN_WRITE TOKEN_LPAREN term TOKEN_RPAREN	{ $$ = stmt_create(STMT_PRINT, 0, 0, $3, 0, 0, 0, 0); }
	| name TOKEN_EQUAL TOKEN_DIGIT	{ $$ = stmt_create(STMT_EXPR, 0, 0, expr_create(EXPR_ADD, expr_create_name($1), expr_create_integer_literal(atoi(yytext))), 0, 0, 0, 0); }
	| name TOKEN_EQUAL TOKEN_STR	{ $$ = stmt_create(STMT_EXPR, 0, 0, expr_create(EXPR_ADD, expr_create_name($1), expr_create_string_literal(strdup(yytext))), 0, 0, 0, 0); }
	;

type : TOKEN_INT	{ $$ = type_create(TYPE_INTEGER, 0, 0); }
	| TOKEN_STRING	{ $$ = type_create(TYPE_STRING, 0, 0); }
	;

name : TOKEN_VARIABLE	{ $$ = yytext; }
	;
%%

int yyerror( char *s ) {
	printf("parse error: %s\n",s);
	return 1;
}
