#ifndef GAME_H
#define GAME_H

#include "../sealapi/include/sealapi.h"
#include "cell.h"
#include <stdbool.h>

/*
int arr[3][4] = {
	{1,1,1,1},
	{2,2,2,2},
	{3,3,3,3}
}; */

extern bool DEBUG;
extern float FRICTION;
extern int ROWS;
extern int COLS;
extern int WIDTH;
extern int HEIGHT;
extern char* TITLE;
extern int FPS;

void start();
void update();
void late_update();
void finish();

#endif