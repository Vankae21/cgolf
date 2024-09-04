#ifndef LEVEL_H
#define LEVEL_H

#include <raylib.h>

extern int LEVEL_SIZE;
extern int LEVEL_BUTTON_SIZE;

typedef struct {
	char* map;
	unsigned i;
} Level;

Level* init_level(unsigned i, char* map);
Level** init_levels();

void check_levels_input(Level** levels);
void draw_level(Level* l, Vector2 pos, Font font);
void draw_levels(Level** levels, Font font);

#endif