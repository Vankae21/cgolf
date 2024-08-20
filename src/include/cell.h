#ifndef CELL_H
#define CELL_H

#include <raylib.h>

extern int CELL_SIZE;
extern Color CELL_COLOR_0, CELL_COLOR_1, CELL_WALL_COLOR;

typedef struct {
	Rectangle rec;
	unsigned i;
	enum {
		GROUND,
		WALL,
	} type;
} Cell;

Cell* init_cell(unsigned i, unsigned type);
Cell** init_cells(char* map, unsigned rows, unsigned cols);
void draw_cell(Cell* cell);
void draw_cells(Cell** cells);


#endif