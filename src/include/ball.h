#ifndef BALL_H
#define BALL_H

#include "soundmanager.h"
#include <raylib.h>

typedef struct {
	Color color, out_color, point_color, line_color;
	Vector2 pos, velo;
	unsigned shot_count;
	float radius, shrink_radius, out_rad, point_rad, line_thick;
	bool is_in_sand, can_get_shot;
} Ball;

Ball* init_ball();
void update_ball(Ball* ball, SoundManager* sman);
void draw_ball(Ball* ball);

#endif