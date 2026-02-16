typedef enum{
	TOKEN_EOF = 0,
	TOKEN_WRITE,      // System.out.println
	TOKEN_IF,	  // if
	TOKEN_FOR,        // for
	TOKEN_TRUE,       // true
	TOKEN_INT,        // int(type)
	TOKEN_STRING,     // String(type)
	TOKEN_VARIABLE,   // VARIABLE
	TOKEN_DIGIT,      // DIGIT
	TOKEN_STR,        // ""
	TOKEN_LPAREN,     // (
	TOKEN_RPAREN,     // )
	TOKEN_LBRACE,     // {
	TOKEN_RBRACE,     // }
	TOKEN_SEMICOLON,  // ;
	TOKEN_EQUAL,      // =
	TOKEN_PLUS,       // +
	TOKEN_MINUS,      // -
	TOKEN_MULT,       // *
	TOKEN_DIV,        // /
	TOKEN_SMALLER,    // <
	TOKEN_LARGER,     // >
	TOKEN_HASH,       // #
	TOKEN_ERROR
} token_t;
