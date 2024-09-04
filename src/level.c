#include "include/level.h"
#include "include/game.h"
#include "include/vutils.h"
#include "sealapi/include/sealapi.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

int LEVEL_SIZE;
int LEVEL_BUTTON_SIZE;

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
	LEVEL_BUTTON_SIZE = seal_int(seal, "LEVEL_BUTTON_SIZE");
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

void draw_level(Level* l, Vector2 pos, Font font)
{
	float font_size = 32;
	DrawRectangle(pos.x, pos.y, LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE, RAYWHITE);
	char level_i[16];
	sprintf(level_i, "%d", l->i + 5);
	Vector2 text_measure = MeasureTextEx(font, level_i, font_size, 0);
	
	Vector2 text_pos = xy(pos.x + (LEVEL_BUTTON_SIZE - text_measure.x) / 2, pos.y + (LEVEL_BUTTON_SIZE - text_measure.y) / 2);
	if (DEBUG)
		DrawRectangleV(text_pos, text_measure, RED);
	DrawTextEx(font, level_i, text_pos, font_size, 0, BLACK);
}

void draw_levels(Level** levels, Font font)
{
	Vector2 pos = xy(0, 0);
	for (int i = 0; i < LEVEL_SIZE; i++) {
		draw_level(levels[i], pos, font);
		pos.x += LEVEL_BUTTON_SIZE * 2;
		if ((i + 1) % 3 == 0) {
			pos.y += LEVEL_BUTTON_SIZE * 2;
			pos.x = 0;
		}
	}	
}