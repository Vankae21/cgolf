#include "include/cell.h"
#include "include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CELL_SIZE;
Color CELL_GROUND_COLOR, CELL_SAND_COLOR, CELL_WALL_COLOR, CELL_HOLE_COLOR;
float SAND_SPEED_DECREASE;

Cell* init_cell(unsigned i, unsigned type)
{
	Cell* cell = calloc(1, sizeof(Cell));
	cell->rec = (Rectangle) { (i % COLS) * CELL_SIZE, (i / COLS) * CELL_SIZE, CELL_SIZE, CELL_SIZE };
	cell->i = i;
	cell->type = type;
	cell->slowed_down = false;

	cell->upper_cell = (void*)0;
	cell->lower_cell = (void*)0;
	cell->right_cell = (void*)0;
	cell->left_cell = (void*)0;	

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
			case 'o':
			case 'O':
			case '0':
				type = HOLE;
				map_i++;
				break;
			case 's':
			case 'S':
				type = SAND;
				map_i++;
				break;
			default:
				map_i++;
				goto loop;
		}
		cells[i] = init_cell(i, type);
	}

	for (int i = 0; i < rows * cols; i++) {
		if (i - COLS >= 0) {
			if (cells[i - COLS]->type == WALL) {				
				cells[i]->upper_cell = cells[i - COLS];
			}
		}
		if (i + COLS < ROWS * COLS) {
			if (cells[i + COLS]->type == WALL) {				
				cells[i]->lower_cell = cells[i + COLS];
			}
		}
		if (i - 1 >= 0) {
			if (cells[i - 1]->type == WALL) {				
				cells[i]->left_cell = cells[i - 1];
			}
		}
		if (i + 1 < ROWS * COLS) {
			if (cells[i + 1]->type == WALL) {				
				cells[i]->right_cell = cells[i + 1];
			}
		}
	}

	return cells;
}

void draw_cell(Cell* cell)
{
	Color color;
	switch (cell->type) {
		case GROUND:
		case HOLE:
			color = CELL_GROUND_COLOR;
			break;
		case SAND:
			color = CELL_SAND_COLOR;
			break;
		case WALL:
			color = CELL_WALL_COLOR;
			break;
	}
	
	DrawRectangleRec(cell->rec, cell->type != WALL ? color : CELL_WALL_COLOR);
	if (cell->type == HOLE) {
		DrawCircle(cell->rec.x + cell->rec.width / 2,
				   cell->rec.y + cell->rec.height / 2,
				   cell->rec.height/2.5, CELL_HOLE_COLOR);		
	}
	if (DEBUG) {
		DrawRectangleLinesEx(cell->rec, 1, BLACK);
	}
}

void draw_cells(Cell** cells, bool draw_wall)
{
	for (int i = 0; cells[i]; i++) {
		if ((draw_wall && cells[i]->type == WALL) || (!draw_wall && cells[i]->type != WALL))
			draw_cell(cells[i]);
	}
}

void change_cells(char* map, Cell** cells, unsigned rows, unsigned cols)
{
	if (strlen(map) < rows * cols) {
		printf("Error: map is missing\n");
		exit(1);
	}

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
			case 'o':
			case 'O':
			case '0':
				type = HOLE;
				map_i++;
				break;
			case 's':
			case 'S':
				type = SAND;
				map_i++;
				break;
			default:
				map_i++;
				goto loop;
		}
		cells[i]->type = type;
		cells[i]->slowed_down = false;
	}

	for (int i = 0; i < rows * cols; i++) {
		cells[i]->upper_cell = (void*)0;
		cells[i]->lower_cell = (void*)0;
		cells[i]->right_cell = (void*)0;
		cells[i]->left_cell = (void*)0;	

		if (i - COLS >= 0) {
			if (cells[i - COLS]->type == WALL) {
				cells[i]->upper_cell = cells[i - COLS];
			}
		}
		if (i + COLS < ROWS * COLS) {
			if (cells[i + COLS]->type == WALL) {
				cells[i]->lower_cell = cells[i + COLS];
			}
		}
		if (i - 1 >= 0) {
			if (cells[i - 1]->type == WALL) {
				cells[i]->left_cell = cells[i - 1];
			}
		}
		if (i + 1 < ROWS * COLS) {
			if (cells[i + 1]->type == WALL) {
				cells[i]->right_cell = cells[i + 1];
			}
		}
	}
}