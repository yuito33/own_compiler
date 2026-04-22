#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct expr;
struct stmt;
struct decl;
struct param_list;
struct type;

/********************************
	  TYPES
********************************/

typedef enum {
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_VOID,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION
} type_t;



struct type {
	type_t kind;
	struct type *subtype;
	struct param_list *params;
};


struct param_list {
	char *name;
	struct type *type;
	struct param_list *next;
};



struct type * type_create( type_t kind,
                           struct type *subtype,
                           struct param_list *params )
{
    struct type *t = malloc(sizeof(*t));

    t->kind = kind;
    t->subtype = subtype;
    t->params = params;

    return t;
}




struct param_list * param_list_create( char *name,
                                       struct type *type,
                                       struct param_list *next )
{
    struct param_list *p = malloc(sizeof(*p));

    p->name = name;
    p->type = type;
    p->next = next;

    return p;
}

void type_print(struct type *t);
void param_list_print(struct param_list *p);
void expr_print(struct expr *e);
void decl_print(struct decl *d);
void stmt_print(struct stmt *s);


void type_print(struct type *t)
{
    if(!t) return;

    switch(t->kind) {
        case TYPE_VOID: printf("void"); break;
        case TYPE_BOOLEAN: printf("bool"); break;
        case TYPE_CHARACTER: printf("char"); break;
        case TYPE_INTEGER: printf("int"); break;
        case TYPE_STRING: printf("string"); break;

        case TYPE_ARRAY:
            printf("array of ");
            type_print(t->subtype);
            break;

        case TYPE_FUNCTION:
            printf("function ");
            type_print(t->subtype); // return type
            if(t->params) {
	        printf(" (");
	        param_list_print(t->params);
	        printf(")");
	    }
            
            break;
    }
}


void param_list_print(struct param_list *p)
{
    if(!p) return;

    printf("%s: ", p->name);
    type_print(p->type);

    if(p->next) {
        printf(", ");
        param_list_print(p->next);
    }
}


/********************************
	EXPRESSIONS
********************************/

typedef enum {
        EXPR_ADD,
        EXPR_SUB,
        EXPR_MUL,
        EXPR_DIV,
        EXPR_NAME,
        EXPR_INTEGER_LITERAL,
        EXPR_STRING_LITERAL,

	EXPR_EQ,
	EXPR_NE,
	EXPR_LT,
	EXPR_LE,
	EXPR_GT,
	EXPR_GE
} expr_t;


struct expr {
        expr_t kind;
        struct expr *left;
        struct expr *right;
        const char *name;
        int integer_value;
        const char *string_literal;
};



struct expr * expr_create(expr_t kind, struct expr *left, struct expr *right )
{
	struct expr *e = malloc(sizeof(*e));
	e->kind = kind;
	e->left = left;
	e->right = right;
        e->name = '\0';
        e->integer_value = 0;
        e->string_literal = '\0';
	return e;
}

struct expr * expr_create_name( const char *n )
{
	struct expr *e = expr_create(EXPR_NAME,0,0);
	e->name = n;
	return e;
}

struct expr * expr_create_integer_literal( int i )
{
	struct expr *e = expr_create(EXPR_INTEGER_LITERAL,0,0);
	e->integer_value = i;
	return e;
}

struct expr * expr_create_string_literal( const char *str )
{
	struct expr *e = expr_create(EXPR_STRING_LITERAL,0,0);
	e->string_literal = str;
	return e;
}



// struct expr * expr_create_boolean_literal( int b );
// struct expr * expr_create_char_literal( char c );



void expr_print( struct expr *e )
{
	if(!e) return;
		printf("(");
	
	expr_print(e->left);
	switch(e->kind) {
		case EXPR_INTEGER_LITERAL: 	printf("%d",e->integer_value); break;
		case EXPR_ADD: 		printf("+"); break;
		case EXPR_SUB: printf("-"); break;
		case EXPR_MUL: printf("*"); break;
		case EXPR_DIV: 	printf("/"); break;
	}
	expr_print(e->right);
	printf(")");
}



/********************************
	DECLARATIONS
********************************/

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct decl *next;
};

struct decl * decl_create( char *name,
                           struct type *type,
                           struct expr *value,
                           struct stmt *code,
                           struct decl *next )
{
	struct decl *d = malloc(sizeof(*d));
	d->name = name;
	d->type = type;
	d->value = value;
	d->code = code;
	d->next = next;

	return d;
}


void decl_print(struct decl *e )
{
	if(!e) return;
		
	printf("var ["); 
	printf("%s",e->name); 
	printf("] : "); 

        type_print(e->type);

	if(e->value) {
	    printf(" = expr "); 
	    expr_print(e->value);
	}	
	 
	if(e->code) {
		printf(" code  ");
	        stmt_print(e->code);
	} else {
	        printf(";\n");
	}

	decl_print(e->next);

}



/********************************
	STATEMENTS
********************************/

typedef enum {
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;


struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};




struct stmt * stmt_create( stmt_t kind,
                           struct decl *decl, struct expr *init_expr,
                           struct expr *expr, struct expr *next_expr,
                           struct stmt *body, struct stmt *else_body,
                           struct stmt *next )
{
    struct stmt *s = malloc(sizeof(*s));

    s->kind = kind;
    s->decl = decl;
    s->init_expr = init_expr;
    s->expr = expr;
    s->next_expr = next_expr;
    s->body = body;
    s->else_body = else_body;
    s->next = next;

    return s;
}


void type_print(struct type *t);
void param_list_print(struct param_list *p);
void expr_print(struct expr *e);
void decl_print(struct decl *d);
void stmt_print(struct stmt *s);

void stmt_print(struct stmt *s)
{
    if(!s) return;

    switch(s->kind) {

        case STMT_DECL:
            decl_print(s->decl);
            break;

        case STMT_EXPR:
            expr_print(s->expr);
            printf(";\n");
            break;

        case STMT_PRINT:
            printf("print ");
            expr_print(s->expr);
            printf(";\n");
            break;

        case STMT_RETURN:
            printf("return ");
            expr_print(s->expr);
            printf(";\n");
            break;

        case STMT_IF_ELSE:
            printf("if (");
            expr_print(s->expr);
            printf(")\n");
            stmt_print(s->body);

            if(s->else_body) {
                printf("else\n");
                stmt_print(s->else_body);
            }
            break;

        case STMT_FOR:
            printf("for (");
            expr_print(s->init_expr);
            printf("; ");
            expr_print(s->expr);
            printf("; ");
            expr_print(s->next_expr);
            printf(")\n");
            stmt_print(s->body);
            break;

        case STMT_BLOCK:
            printf("{\n");
            stmt_print(s->body);
            printf("}\n");
            break;
    }

    stmt_print(s->next);
}

//stdout = original;
