#ifndef GAME_H
#define GAME_H

#include "../sealapi/include/sealapi.h"
#include "ball.h"
#include "cell.h"
#include "level.h"
#include "particle.h"
#include <stdbool.h>
#include <stdlib.h>

/*
int arr[3][4] = {
	{1,1,1,1},
	{2,2,2,2},
	{3,3,3,3}
};
*/

extern bool DEBUG;
extern float FRICTION;
extern int ROWS;
extern int COLS;
extern int WIDTH;
extern int HEIGHT;
extern char* TITLE;
extern int FPS;
extern size_t PARTICLE_MAX_SIZE;

typedef enum {
	MENU,
	LEVEL_SELECTION,
	GAME,
	PAUSE
} GameState;

extern GameState GAME_STATE;

void start();
void update();
void late_update();
void finish();

// ball
void reset_ball(Ball* ball);

// level
void load_level(Level** levels, Ball* ball, Particle** particles, unsigned map_i);
void load_next_level(Level** levels, Ball* ball, Particle** particles, unsigned* map_i);

void quit_game();

#endif