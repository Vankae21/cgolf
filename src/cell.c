#include "include/cell.h"
#include "include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CELL_SIZE;
Color CELL_COLOR_0, CELL_COLOR_1, CELL_WALL_COLOR;

Cell* init_cell(unsigned i, unsigned type)
{
	Cell* cell = calloc(1, sizeof(Cell));
	cell->rec = (Rectangle) { (i % COLS) * CELL_SIZE, (i / COLS) * CELL_SIZE, CELL_SIZE, CELL_SIZE };
	cell->i = i;
	cell->type = type;

	return cell;
}

Cell** init_cells(char* map, unsigned rows, unsigned cols)
{
	if (strlen(map) < rows * cols) {
		printf("Error: map is missing\n");
		exit(1);
	}
	Cell** cells = calloc(rows * cols, sizeof(Cell*));

	unsigned map_i = 0;
	for (int i = 0; i < rows * cols; i++) {
		unsigned type;
		
		loop:
		if (map[map_i] == '\0') {
			break;
		}
		switch (map[map_i]) {
			case 'g':
			case 'G':
				type = GROUND;
				map_i++;
				break;
			case 'w':
			case 'W':
				type = WALL;
				map_i++;
				break;
			default:
				map_i++;
				goto loop;
		}
		cells[i] = init_cell(i, type);
	}

	return cells;
}

void draw_cell(Cell* cell)
{
	unsigned i = cell->i;
	Color color = ((i % COLS) + (i / COLS)) % 2 == 0 ? CELL_COLOR_0 : CELL_COLOR_1;
	
	DrawRectangleRec(cell->rec, cell->type == GROUND ? color : CELL_WALL_COLOR);

	if (DEBUG) {
		DrawRectangleLinesEx(cell->rec, 1, BLACK);
	}
}

void draw_cells(Cell** cells)
{
	for (int i = 0; cells[i]; i++) {
		draw_cell(cells[i]);
	}
}