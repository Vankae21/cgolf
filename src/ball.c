#include "include/ball.h"
#include "include/game.h"
#include "include/vutils.h"
#include "sealapi/include/sealapi.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

Ball* init_ball()
{
	Ball* ball = calloc(1, sizeof(Ball));

	SEAL* seal = seal_data("seal/ball.seal");

	ball->color = (Color) { seal_int(seal, "r"), seal_int(seal, "g"), seal_int(seal, "b"), 255 };
	ball->out_color = (Color) { seal_int(seal, "outr"), seal_int(seal, "outg"), seal_int(seal, "outb"), seal_int(seal, "outa") };
	ball->line_color = (Color) { seal_int(seal, "lr"), seal_int(seal, "lg"), seal_int(seal, "lb"), seal_int(seal, "la") };
	ball->point_color = (Color) { seal_int(seal, "pr"), seal_int(seal, "pg"), seal_int(seal, "pb"), seal_int(seal, "pa") };
	ball->pos = (Vector2) { seal_float(seal, "x"), seal_float(seal, "y") };
	ball->radius = seal_float(seal, "radius");
	ball->out_rad = seal_float(seal, "out_rad");
	ball->point_rad = seal_float(seal, "point_rad");
	ball->line_thick = seal_float(seal, "line_thick");

	return ball;
}

void update_ball(Ball* ball)
{
	Vector2 mouse = GetMousePosition();

	float distance = vec2_distance(ball->pos, mouse);
	distance *= sqrt(distance);
	Vector2 dir = vec2_normalize((Vector2) { mouse.x - ball->pos.x, mouse.y - ball->pos.y });

	float speed = 1;
	if (IsMouseButtonPressed(0)) {
		ball->velo = (Vector2) { .x = dir.x * distance * speed, .y = dir.y * distance * speed };
	}

	ball->pos.x += ball->velo.x * GetFrameTime();
	ball->pos.y += ball->velo.y * GetFrameTime();

	if (ball->velo.x != 0 || ball->velo.y != 0) {
		ball->velo.x *= FRICTION;
		ball->velo.y *= FRICTION;
	}
}

void draw_ball(Ball* ball)
{
	DrawCircleV(ball->pos, ball->out_rad, ball->out_color);
	DrawCircleV(ball->pos, ball->radius, ball->color);

	if (DEBUG) {
		DrawCircleV(ball->pos, ball->point_rad, ball->point_color);
	}

	Vector2 mouse = GetMousePosition();
	float distance = vec2_distance(ball->pos, mouse);
	Color line_color = (Color) { 255, 255 - clamp(distance/1.8f, 0, 255) , 0, 255 };
	DrawLineEx(ball->pos, mouse, ball->line_thick, line_color);
}