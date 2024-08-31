#include "include/level.h"
#include "sealapi/include/sealapi.h"
#include <stdlib.h>
#include <stdio.h>

int LEVEL_SIZE;

Level* init_level(unsigned i, char* map)
{
	Level* level = calloc(1, sizeof(Level));

	level->i = i;
	level->map = map;

	return level;
}

Level** init_levels()
{
	SEAL* seal = seal_data("seal/level.seal");
	LEVEL_SIZE = seal_int(seal, "LEVEL_SIZE");
	Level** levels = calloc(LEVEL_SIZE, sizeof(Level*));

	for (int i = 0; i < LEVEL_SIZE; i++) {
		char level_name[32];
		sprintf(level_name, "map%d", i);
		char* map = seal_string(seal, level_name);
		levels[i] = init_level(i, map);
	}

	return levels;
}

void check_levels_input(Level** levels)
{

}

void draw_levels(Level** levels)
{
	for (int i = 0; i < LEVEL_SIZE; i++) {
		
	}	
}