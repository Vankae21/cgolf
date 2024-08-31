#ifndef CELL_H
#define CELL_H

#include <raylib.h>
#include <stdbool.h>

extern int CELL_SIZE;
extern Color CELL_GROUND_COLOR, CELL_SAND_COLOR, CELL_WALL_COLOR, CELL_HOLE_COLOR;
extern float SAND_SPEED_DECREASE;

typedef struct Cell {
	Rectangle rec;
	unsigned i;
	enum {
		GROUND,
		SAND,
		WALL,
		HOLE,
	} type;
	bool slowed_down;

	struct Cell *upper_cell,
		 		*lower_cell,
				*right_cell,
				*left_cell;
} Cell;

Cell* init_cell(unsigned i, unsigned type);
Cell** init_cells(char* map, unsigned rows, unsigned cols);
void draw_cell(Cell* cell);
void draw_cells(Cell** cells, bool draw_wall);
void change_cells(char* map, Cell** cells, unsigned rows, unsigned cols);

#endif