#ifndef BALL_H
#define BALL_H

#include <raylib.h>

typedef struct {
	Color color, out_color, point_color, line_color;
	Vector2 pos, velo;
	float radius, out_rad, point_rad, line_thick;
} Ball;

Ball* init_ball();
void update_ball(Ball* ball);
void draw_ball(Ball* ball);

#endif