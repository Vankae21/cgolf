#include "include/game.h"
#include "include/ball.h"
#include "include/cell.h"
#include "include/vutils.h"
#include "sealapi/include/sealapi.h"
#include <raylib.h>
#include <stdio.h>

bool DEBUG;
float FRICTION;
int ROWS;
int COLS;
int WIDTH;
int HEIGHT;
char* TITLE;
int FPS;

Cell** cells = (void*)0;
Ball* ball = (void*)0;

void start()
{
	// cell.seal
	SEAL* cell_seal = seal_data("seal/cell.seal"), *game_seal = seal_data("seal/game.seal");;
	CELL_COLOR_0 = (Color) { seal_int(cell_seal, "r0"), seal_int(cell_seal, "g0"), seal_int(cell_seal, "b0"), 255 };
	CELL_COLOR_1 = (Color) { seal_int(cell_seal, "r1"), seal_int(cell_seal, "g1"), seal_int(cell_seal, "b1"), 255 };
	CELL_WALL_COLOR = (Color) { seal_int(cell_seal, "wr"), seal_int(cell_seal, "wg"), seal_int(cell_seal, "wb"), 255 };

	cells = init_cells(seal_string(game_seal, "map"), ROWS, COLS);

	// ball
	ball = init_ball();
}

void update()
{
	update_ball(ball);

	if (ball->pos.x - ball->radius < 0) {
		ball->pos.x = ball->radius;
		ball->velo.x *= -1;
	} else if (ball->pos.x + ball->radius > WIDTH) {
		ball->pos.x = WIDTH - ball->radius;
		ball->velo.x *= -1;
	}
	if (ball->pos.y - ball->radius < 0) {
		ball->pos.y = ball->radius;
		ball->velo.y *= -1;		
	} else if (ball->pos.y + ball->radius > HEIGHT) {
		ball->pos.y = HEIGHT - ball->radius;
		ball->velo.y *= -1;
	}

	for (int i = 0; i < ROWS * COLS; i++) {
		if (cells[i]->type != WALL) continue;
		Cell* wall = cells[i];

		float closest_x = clamp(ball->pos.x, wall->rec.x, wall->rec.x + wall->rec.width);
		float closest_y = clamp(ball->pos.y, wall->rec.y, wall->rec.y + wall->rec.height);

		Vector2 dist = { ball->pos.x - closest_x, ball->pos.y - closest_y };
		if (vec2_len(dist) <= ball->radius) {
			if (fabs(dist.x) > fabs(dist.y)) {
				if (dist.x > 0) {
					ball->pos.x = wall->rec.x + wall->rec.width + ball->radius;
				} else {
					ball->pos.x = wall->rec.x - ball->radius;
				}
				ball->velo.x *= -1;
			} else {
				if (dist.y > 0) {
					ball->pos.y = wall->rec.y + wall->rec.height + ball->radius;
				} else {
					ball->pos.y = wall->rec.y - ball->radius;
				}
				ball->velo.y *= -1;
			}
		}
	}
}

void late_update()
{
	draw_cells(cells);
	draw_ball(ball);
}

void finish()
{

}
