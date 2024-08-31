#ifndef LEVEL_H
#define LEVEL_H

extern int LEVEL_SIZE;

typedef struct {
	char* map;
	unsigned i;
} Level;

Level* init_level(unsigned i, char* map);
Level** init_levels();

void check_levels_input(Level** levels);
void draw_levels(Level** levels);

#endif