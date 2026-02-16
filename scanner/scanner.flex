%{
#include "token.h"
%}
STR \".*\"
DIGIT [0-9]
LETTER [a-zA-Z]
VARIABLE {LETTER}+({DIGIT}|{LETTER})*
%%
(" "|\t|\n) /* skip whitespace */
System\.out\.println { return TOKEN_WRITE; }
if                   { return TOKEN_IF; }
for                  { return TOKEN_FOR; }
true                 { return TOKEN_TRUE; }
int                  { return TOKEN_INT; }
String               { return TOKEN_STRING; }
{VARIABLE}           { return TOKEN_VARIABLE; }
{DIGIT}+             { return TOKEN_DIGIT; }
{STR}                { return TOKEN_STR; }
\(                   { return TOKEN_LPAREN; }
\)                   { return TOKEN_RPAREN; }
\{                   { return TOKEN_LBRACE; }
\}                   { return TOKEN_RBRACE; }
\;                   { return TOKEN_SEMICOLON; }
\=                   { return TOKEN_EQUAL; }
\+                   { return TOKEN_PLUS; }
\-                   { return TOKEN_MINUS; }
\*                   { return TOKEN_MULT; }
\/                   { return TOKEN_DIV; }
\<                   { return TOKEN_SMALLER; }
\>                   { return TOKEN_LARGER; }
\#                   { return TOKEN_HASH; }
.                    { return TOKEN_ERROR; }
%%
int yywrap(){
    return 1;
}
