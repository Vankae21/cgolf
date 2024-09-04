#include "include/game.h"
#include "include/ball.h"
#include "include/button.h"
#include "include/cell.h"
#include "include/level.h"
#include "include/soundmanager.h"
#include "include/ui.h"
#include "include/vutils.h"
#include "include/particle.h"
#include "sealapi/include/sealapi.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

bool DEBUG;
float FRICTION;
int ROWS;
int COLS;
int WIDTH;
int HEIGHT;
char* TITLE;
int FPS;
size_t PARTICLE_MAX_SIZE;
GameState GAME_STATE = MENU;
float elapsed_time = 0;

unsigned map_i = 0;

// sound manager
SoundManager* sman = (void*)0;

Cell** cells = (void*)0;
Ball* ball = (void*)0;
Level** levels = (void*)0;
Particle** particles = (void*)0;

// buttons
// main
Button* play_button = (void*)0;
Button* quit_button = (void*)0;
// level
Button** level_buttons = (void*)0;
Button* return_button = (void*)0;
// pause
Button* replay_button = (void*)0;
Button* level_selection_button = (void*)0;

Font font;

void start()
{
	// randomize seed
	srand(time((void*)0));
	// levels
	levels = init_levels();
	// sound manager
	sman = init_sound_manager();
	// seal
	SEAL* cell_seal = seal_data("seal/cell.seal"), *game_seal = seal_data("seal/game.seal"), *button_seal = seal_data("seal/button.seal");
	font = LoadFontEx(seal_string(game_seal, "font_path"), 64, (void*)0, 300);
	CELL_GROUND_COLOR = (Color) { seal_int(cell_seal, "gr"), seal_int(cell_seal, "gg"), seal_int(cell_seal, "gb"), 255 };
	CELL_SAND_COLOR = (Color) { seal_int(cell_seal, "sr"), seal_int(cell_seal, "sg"), seal_int(cell_seal, "sb"), 255 };
	CELL_WALL_COLOR = (Color) { seal_int(cell_seal, "wr"), seal_int(cell_seal, "wg"), seal_int(cell_seal, "wb"), 255 };
	CELL_HOLE_COLOR = (Color) { seal_int(cell_seal, "hr"), seal_int(cell_seal, "hg"), seal_int(cell_seal, "hb"), 255 };
	SAND_SPEED_DECREASE = seal_float(cell_seal, "SAND_SPEED_DECREASE");

	cells = init_cells(levels[map_i]->map, ROWS, COLS);
	// ball
	ball = init_ball();
	// particles
	particles = calloc(PARTICLE_MAX_SIZE, sizeof(Particle*));
	for (int i = 0; i < PARTICLE_MAX_SIZE; i++) {
		particles[i] = calloc(1, sizeof(Particle));
		particles[i]->is_active = false;
	}

	// buttons
	int _BUTTON_X = seal_int(button_seal, "BUTTON_X"), _BUTTON_Y = seal_int(button_seal, "BUTTON_Y");
	play_button = init_button(xy(_BUTTON_X, _BUTTON_Y), xy((WIDTH - _BUTTON_X)/2, (HEIGHT - _BUTTON_Y * 4)/2), "play", 32);
	quit_button = init_button(xy(_BUTTON_X, _BUTTON_Y), xy((WIDTH - _BUTTON_X)/2, (HEIGHT - _BUTTON_Y)/2), "quit", 32);
	return_button = init_button(xy(_BUTTON_Y, _BUTTON_Y), xy(24, 24), "<", 32);
	replay_button = init_button(xy(_BUTTON_X, _BUTTON_Y), xy((WIDTH - _BUTTON_X)/2, (HEIGHT - _BUTTON_Y * 4)/2), "replay", 32);
	level_selection_button = init_button(xy(_BUTTON_X, _BUTTON_Y), xy((WIDTH - _BUTTON_X)/2, (HEIGHT - _BUTTON_Y)/2), "levels", 32);

	level_buttons = calloc(LEVEL_SIZE, sizeof(Button*));
	float lvl_btn_gap = LEVEL_BUTTON_SIZE + 64;
	Vector2 lvl_btn_pos = xy((WIDTH - lvl_btn_gap * 2 - LEVEL_BUTTON_SIZE)/2, lvl_btn_gap);
	float lvl_btn_font_size = 32;
	for (int i = 0; i < LEVEL_SIZE; i++) {
		char lvl_i_text[32];
		sprintf(lvl_i_text, "%d", i + 1);
		level_buttons[i] = init_button(xy(LEVEL_BUTTON_SIZE, LEVEL_BUTTON_SIZE), lvl_btn_pos, strdup(lvl_i_text), lvl_btn_font_size);
		lvl_btn_pos.x += lvl_btn_gap;
		if ((i + 1) % 3 == 0) {
			lvl_btn_pos.x = (WIDTH - lvl_btn_gap * 2 - LEVEL_BUTTON_SIZE)/2;
			lvl_btn_pos.y += lvl_btn_gap;
		}
	}
}

void update()
{
	if (GAME_STATE == MENU) {
		if (is_button_pressed(play_button)) {
			GAME_STATE = LEVEL_SELECTION;
		} else if (is_button_pressed(quit_button)) {
			quit_game();
		}
		return;
	} else if (GAME_STATE == LEVEL_SELECTION) {
		for (int i = 0; i < LEVEL_SIZE; i++) {
			if (is_button_pressed(level_buttons[i])) {
				// start the level
				GAME_STATE = GAME;
				map_i = i;
				load_level(levels, ball, particles, map_i);
			}
		}
		if (is_button_pressed(return_button)) {
			GAME_STATE = MENU;
		}
		return;
	}
	if (DEBUG) {		
		if (IsKeyPressed(KEY_LEFT)) {
			map_i -= 2;
			load_next_level(levels, ball, particles, &map_i);
		} else if (IsKeyPressed(KEY_RIGHT)) {
			load_next_level(levels, ball, particles, &map_i);
		}
	}
	if (IsKeyPressed(KEY_R)) {
		load_level(levels, ball, particles, map_i);
	} else if (IsKeyPressed(KEY_ESCAPE)) {
		GAME_STATE = GAME_STATE == PAUSE ? GAME : PAUSE;
	}
	if (GAME_STATE == PAUSE) {
		if (is_button_pressed(replay_button)) {
			load_level(levels, ball, particles, map_i);
		} else if (is_button_pressed(level_selection_button)) {
			GAME_STATE = LEVEL_SELECTION;
		}
		return;
	}
	if (ball->shot_count > 0) {
		elapsed_time += GetFrameTime();
	}
	update_ball(ball, sman);
	update_particles(particles);

	bool is_collided_border = false;
	if (ball->pos.x - ball->radius < 0) {
		ball->pos.x = ball->radius;
		ball->velo.x *= -1;
		is_collided_border = true;	
	} else if (ball->pos.x + ball->radius > WIDTH) {
		ball->pos.x = WIDTH - ball->radius;
		ball->velo.x *= -1;
		is_collided_border = true;
	}
	if (ball->pos.y - ball->radius < 0) {
		ball->pos.y = ball->radius;
		ball->velo.y *= -1;		
		is_collided_border = true;
	} else if (ball->pos.y + ball->radius > HEIGHT) {
		ball->pos.y = HEIGHT - ball->radius;
		ball->velo.y *= -1;
		is_collided_border = true;
	}

	if (is_collided_border) {
		create_particles(particles, 10, ball->pos,
										vec2_mul(vec2_normalize(ball->velo), -1),
										DARKGRAY, 100, 8, 1);
	}

	bool is_in_sand = false;
	for (int i = 0; i < ROWS * COLS; i++) {
		Cell* cell = cells[i];

		if (cell->type == SAND) {
			if (is_rec_circle_colliding(cell->rec, (Circle) { ball->pos, ball->radius })) {
//				ball->is_in_sand = true;
				is_in_sand = true;
				if (!cell->slowed_down) {
					ball->velo.x *= SAND_SPEED_DECREASE;
					ball->velo.y *= SAND_SPEED_DECREASE;
					cell->slowed_down = true;
					
				}
				create_particles(particles, 1, ball->pos,
									 vec2_mul(vec2_normalize(ball->velo), -1),
									 ORANGE, 100, 8, 1);
			} else {
				cell->slowed_down = false;
			}
			continue;
		} if (cell->type == HOLE) {
			// check collisions
			Vector2 hole_center = { cell->rec.x + cell->rec.width / 2, 
									cell->rec.y + cell->rec.height / 2 };
			float hole_radius = cell->rec.height/2.5;
			if (are_circles_colliding(
				(Circle) {ball->pos, ball->radius},
				(Circle) {hole_center, hole_radius} )) {

				float coll_perc = (1 - vec2_distance(ball->pos, hole_center) /
										(ball->radius + hole_radius))
								   			* 100;
		//		printf("%f\n", coll_perc);
				if (coll_perc >= 60) {
					// win right here
					ball->pos = hole_center;
					ball->velo = (Vector2) {0};
					ball->can_get_shot = false;
					if (ball->radius > 0) {
						ball->radius -= 20 * GetFrameTime();
						play_ball_in_hole_sound(sman);
					} else {
						load_next_level(levels, ball, particles, &map_i);
					}
				}
			}
			continue;
		} else if (cell->type != WALL) {
			continue;
		}

		float closest_x = clamp(ball->pos.x, cell->rec.x, cell->rec.x + cell->rec.width);
		float closest_y = clamp(ball->pos.y, cell->rec.y, cell->rec.y + cell->rec.height);

		Vector2 dist = { ball->pos.x - closest_x, ball->pos.y - closest_y };
		if (vec2_len(dist) <= ball->radius) {
			if (fabs(dist.x) > fabs(dist.y)) {
				if (dist.x > 0 && !cell->right_cell) {
					ball->pos.x = cell->rec.x + cell->rec.width + ball->radius;
					ball->velo.x *= -1;
				} else if (dist.x < 0 && !cell->left_cell) {
					ball->pos.x = cell->rec.x - ball->radius;
					ball->velo.x *= -1;
				}
			} else {
				if (dist.y > 0 && !cell->lower_cell) {
					ball->pos.y = cell->rec.y + cell->rec.height + ball->radius;
					ball->velo.y *= -1;
				} else if (dist.y < 0 && !cell->upper_cell) {
					ball->pos.y = cell->rec.y - ball->radius;
					ball->velo.y *= -1;
				}
			}
			create_particles(particles, 10, ball->pos,
											vec2_mul(vec2_normalize(ball->velo), -1),
											DARKGRAY, 100, 8, 1);
		}
	}
	ball->is_in_sand = is_in_sand;
}

void late_update()
{
	// background ---
	{
		DrawRectangle(0, 0, WIDTH, HEIGHT, CELL_GROUND_COLOR);
		float font_size = 64;
		Vector2 text_measure = MeasureTextEx(font, TITLE, font_size, 0);
		DrawTextEx(font, TITLE, xy((WIDTH - text_measure.x)/2, 16), font_size, 0, BLACK);
	}
	// --------------
	if (GAME_STATE == MENU) {
		draw_button(play_button, font);
		draw_button(quit_button, font);
		return;
	} else if (GAME_STATE == LEVEL_SELECTION) {
		for (int i = 0; i < LEVEL_SIZE; i++) {
			draw_button(level_buttons[i], font);
		}
		draw_button(return_button, font);
		return;
	}

	draw_cells(cells, false);
	draw_particles(particles);
	draw_cells(cells, true);
	draw_ball(ball);

	if (GAME_STATE == PAUSE) {
		DrawRectangle(0, 0, WIDTH, HEIGHT, (Color) { 0, 0, 0, 100 });
		draw_button(replay_button, font);
		draw_button(level_selection_button, font);
	}

	// UI ----------

//	ui_draw_shot_count(font, ball->shot_count);
	ui_draw_timer(font, elapsed_time);
}

void finish() { }

// ball
void reset_ball(Ball* ball)
{
	SEAL* seal = seal_data("seal/ball.seal");
	ball->pos = (Vector2) { seal_float(seal, "x"), seal_float(seal, "y") };
	ball->velo = (Vector2) {0};
	ball->radius = seal_float(seal, "radius");
	ball->can_get_shot = true;
	ball->is_in_sand = false;
	ball->shot_count = 0;
}

// level
void load_level(Level** levels, Ball* ball, Particle** particles, unsigned map_i)
{
	if (map_i >= LEVEL_SIZE || map_i < 0) {
		GAME_STATE = LEVEL_SELECTION;
		return;
	}

	change_cells(levels[map_i]->map, cells, ROWS, COLS);
	deactivate_all_particles(particles);
	reset_ball(ball);
	GAME_STATE = GAME;
	elapsed_time = 0;
}

void load_next_level(Level** levels, Ball* ball, Particle** particles, unsigned* map_i)
{
	(*map_i)++;

	load_level(levels, ball, particles, *map_i);
}

void quit_game()
{
	finish();
	exit(0);
}