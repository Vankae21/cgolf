#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdbool.h>
#include "datas.h"
#include "lexer.h"

typedef struct {
	size_t token_size;
	Token** tokens;
	unsigned i;
	Data* data_root;
	unsigned scope_i;
} Parser;

Parser* init_parser(Lexer* lexer);

void parser_parse_prompt(Parser* parser, Lexer* lexer);

void parser_parse(Parser* parser);
bool parser_expect(Parser* parser, unsigned type);
Token* parser_eat(Parser* parser, unsigned type);
void parse_statement(Parser* parser); // for phrases end with '.'
void parse_amper(Parser* parser);

Token* parser_peek(Parser* parser);
Token* parser_peek_next(Parser* parser);
Token* parser_advance(Parser* parser);

bool parser_is_end(Parser* parser);

// individually parse
void parse_int(Parser* parser, bool is_const);
void parse_float(Parser* parser, bool is_const);
void parse_char(Parser* parser, bool is_const);
void parse_string(Parser* parser, bool is_const);
void parse_bool(Parser* parser, bool is_const);
void parse_id(Parser* parser, char* name);

// functions
double parse_add(Parser* parser);
double parse_mul(Parser* parser);
double parse_sub(Parser* parser);
double parse_div(Parser* parser);
long parse_mod(Parser* parser);
double parse_pow(Parser* parser);
double parse_sqrt(Parser* parser);
long parse_wdiv(Parser* parser);
double parse_abs(Parser* parser);
void parse_upper(Parser* parser);
void parse_lower(Parser* parser);
double parse_sin(Parser* parser);
double parse_cos(Parser* parser);

void parse_cat(Parser* parser);
void parse_echo(Parser* parser);
void parse_exit(Parser* parser);
void parse_sleep(Parser* parser);
char* parse_read(Parser* parser);
double parse_read_digit(Parser* parser);
double parse_digit(Parser* parser);
long parse_rand(Parser* parser);
long parse_len(Parser* parser);
char* parse_tostring(Parser* parser);

// if while
void parse_if(Parser* parser);
void parse_while(Parser* parser);
void skip_else(Parser* parser);
void parse_else(Parser* parser);

// booleans
bool parse_bool_val(Parser* parser);
bool parse_bool_compl(Parser* parser);
bool parse_eq(Parser* parser);
bool parse_gt(Parser* parser);
bool parse_gtq(Parser* parser);
bool parse_ls(Parser* parser);
bool parse_lsq(Parser* parser);
bool parse_seq(Parser* parser);
bool parse_ceq(Parser* parser);

// string
char* parse_string_val(Parser* parser);

// char
char parse_char_val(Parser* parser);

// skip stop
void parse_skip(Parser* parser);
void parse_stop(Parser* parser);

#endif