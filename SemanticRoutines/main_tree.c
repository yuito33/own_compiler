#include <stdio.h>

extern struct stmt * parser_result;
extern int yyparse();
extern void stmt_print(struct stmt *e );
extern FILE *yyin;

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("File name is missing!\n");
		return -1;
	}
		
	yyin = fopen(argv[1], "r"); // Set Flex's input stream to your file
	if(!yyin) {
		printf("Could not open the program!\n");
		return -1;
	}
	
	if(yyparse()==0) { 		// Start parsing
	  printf("Parse successful!\n AST: \n ------- \n");
	  
	  stmt_print(parser_result);

	  FILE *original = stdout;
          freopen("output.txt", "w", stdout);

	  stmt_print(parser_result);
	  
	  stdout = original;


	  printf("\n");
	} else {
	  printf("Parse failed.\n");
	}
}
