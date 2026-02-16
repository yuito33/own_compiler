# Scanner

## Overview
These programs are used as a Scanner.

## How to execute
1. Check the program.java that will be scanned by a Scanner.
2. Execute following command.
>> gcc -o scan main.c scanner.c
3. Execute following command.
>> scan

## Tokens
	0: TOKEN_EOF = 0,
	1: TOKEN_WRITE,      // System.out.println
	2: TOKEN_IF,	  // if
	3: TOKEN_FOR,        // for
	4: TOKEN_TRUE,       // true
	5: TOKEN_INT,        // int(type)
	6: TOKEN_STRING,     // String(type)
	7: TOKEN_VARIABLE,   // VARIABLE
	8: TOKEN_DIGIT,      // DIGIT
	9: TOKEN_STR,        // ""
	10: TOKEN_LPAREN,     // (
	11: TOKEN_RPAREN,     // )
	12: TOKEN_LBRACE,     // {
	13: TOKEN_RBRACE,     // }
	14: TOKEN_SEMICOLON,  // ;
	15: TOKEN_EQUAL,      // =
	16: TOKEN_PLUS,       // +
	17: TOKEN_MINUS,      // -
	18: TOKEN_MULT,       // *
	19: TOKEN_DIV,        // /
	20: TOKEN_SMALLER,    // <
	21: TOKEN_LARGER,     // >
	22: TOKEN_HASH,       // #
	23: TOKEN_ERROR       // Other
