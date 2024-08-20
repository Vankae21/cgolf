#ifndef DATAS_H
#define DATAS_H

#include "token.h"
#include <stdbool.h>

typedef struct Data {
	Value val;
	char* name;
	enum {
		DATA_INT,
		DATA_FLOAT,
		DATA_CHAR,
		DATA_STRING,
		DATA_BOOL
	} type;
	struct Data* next_data;
	unsigned scope_i;
	bool is_const;
} Data;

char* get_data_type_name(Data* data);
Data* init_data();

void add_data(Data* data_root, unsigned scope_i, bool is_const, char* name, unsigned type, Value val);
Data* search_data(Data* data_root, char* name);
bool is_data_defined(Data* data_root, char* name);
void free_scope_data(Data* data_root, unsigned scope_i);

#endif