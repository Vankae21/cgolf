#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdbool.h>

char* read_file(const char* path);
bool is_seal_file(const char* path);

#endif