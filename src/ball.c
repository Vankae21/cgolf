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
	ball->shrink_radius = seal_float(seal, "shrink_radius");
	ball->out_rad = seal_float(seal, "out_rad");
	ball->point_rad = seal_float(seal, "point_rad");
	ball->line_thick = seal_float(seal, "line_thick");

	ball->shot_count = 0;

	ball->is_in_sand = false;
	ball->can_get_shot = true;

	return ball;
}

void update_ball(Ball* ball)
{
	Vector2 mouse = GetMousePosition();

	float distance = vec2_distance(ball->pos, mouse);
	distance = clamp(distance * 3, 0, 1000);

	Vector2 dir = vec2_normalize((Vector2) { mouse.x - ball->pos.x, mouse.y - ball->pos.y });

	if (IsMouseButtonReleased(0) && ball->can_get_shot) {
		ball->velo = (Vector2) { .x = dir.x * distance, .y = dir.y * distance };
		if (ball->is_in_sand) {
			ball->velo.x *= SAND_SPEED_DECREASE;
			ball->velo.y *= SAND_SPEED_DECREASE;
		}
		ball->can_get_shot = false;
		ball->shot_count++;
	}

	ball->pos.x += ball->velo.x * GetFrameTime();
	ball->pos.y += ball->velo.y * GetFrameTime();

	if (ball->velo.x != 0 || ball->velo.y != 0) {
//		speed -= (speed * (1 - friction)) / fps;
		float mul = 1.4f;
		ball->velo.x -= mul * (ball->velo.x * (1 - FRICTION)) * GetFrameTime();
		ball->velo.y -= mul * (ball->velo.y * (1 - FRICTION)) * GetFrameTime();
//		ball->velo.y *= FRICTION;
	}

	if (!ball->can_get_shot) {
		if (vec2_len(ball->velo) < 10.0f) {
			ball->can_get_shot = true;
		}
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
	float distance = vec2_distance(mouse, ball->pos);
	distance = clamp(distance, 0, 255);
	Color line_color = (Color) { 255, 255 - distance , 0, 255 };
	
	Vector2 dir = vec2_normalize((Vector2) { mouse.x - ball->pos.x, mouse.y - ball->pos.y });
	Vector2 max_line_pos = { .x = ball->pos.x + dir.x * distance, .y = ball->pos.y + dir.y * distance };

	if (IsMouseButtonDown(0) && ball->can_get_shot) {
		DrawLineEx(ball->pos, max_line_pos, ball->line_thick, line_color);
	}
}