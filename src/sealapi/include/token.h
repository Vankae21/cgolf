#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>

typedef union {
	char* s;
	double f;
	long d;
	char c;
	bool b;
} Value;

typedef struct {
	unsigned line;
	enum {
		AMPER, ASSIGN, DOT, COMMA, LPAREN, RPAREN, LBRACK, RBRACK, RSHIFT,

		STRING, INT, FLOAT, BOOL, CHAR,

		STRING_VAL, CHAR_VAL, INT_VAL, FLOAT_VAL, TRUE, FALSE,

		NOT, AND, OR,

		ID,

		IF, ELSE, WHILE, STOP, SKIP,
		
		EQ, GT, GTQ, LS, LSQ, SEQ, CEQ,
		ECHO, SLEEP, EXIT, READ, RAND,
		ADD, MUL, SUB, DIV, MOD, POW, SQRT, LEN, WDIV, ABS, UPPER, LOWER, SIN, COS,
		CAT, TOSTRING,

		EOF_T,
	} type;
	Value val;
} Token;

Token* init_token(unsigned type, char* value, unsigned line);
char* token_get_name(unsigned type);

#endif