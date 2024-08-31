#include "include/ui.h"
#include "include/game.h"
#include "include/vutils.h"
#include <raylib.h>
#include <stdio.h>

void ui_draw_shot_count(Font font, unsigned shot_count)
{
	unsigned font_size = 32;

	char shot_count_text[32];
	sprintf(shot_count_text, "Shot:%d", shot_count);
	Vector2 text_measure = MeasureTextEx(font, shot_count_text, font_size, 0);
	DrawTextEx(font, shot_count_text, xy((WIDTH - text_measure.x) / 2, 0), font_size, 0, BLACK);
}