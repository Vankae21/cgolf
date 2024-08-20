#ifndef SEALAPI_H
#define SEALAPI_H

#include "datas.h"

typedef Data SEAL;

Data* seal_data(const char* path);
long seal_int(Data* root, char* name);
double seal_float(Data* root, char* name);
char seal_char(Data* root, char* name);
char* seal_string(Data* root, char* name);
bool seal_bool(Data* root, char* name);

#endif