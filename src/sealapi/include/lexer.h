#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	unsigned i;
	size_t token_size;
	unsigned line;
	Token** tokens;
	char* content;
} Lexer;

Lexer* init_lexer(char* content);

void lexer_collect_prompt(Lexer* lexer, char* content);

void lexer_collect_tokens(Lexer* lexer);
void lexer_collect_token(Lexer* lexer);

void lexer_get_id(Lexer* lexer);
void lexer_get_string(Lexer* lexer);
void lexer_get_char(Lexer* lexer);
void lexer_get_digit(Lexer* lexer);
void lexer_skip_comment(Lexer* lexer);
void lexer_skip_whitespaces(Lexer* lexer);
char lexer_peek(Lexer* lexer);
char lexer_peek_next(Lexer* lexer);
char lexer_advance(Lexer* lexer);
bool lexer_match(Lexer* lexer);
bool lexer_is_end(Lexer* lexer);
void lexer_add_token(Lexer* lexer, Token* token);

#endif