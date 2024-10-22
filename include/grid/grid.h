#ifndef GRID_H
#define GRID_H

#include "grid_types.h"
#include <SDL2/SDL.h>

void init_grid(grid *g, int height, int width);
void free_grid(grid *g);
void print_grid(grid *g);

void draw_grid(grid *g, SDL_Renderer *renderer, int x, int y, int cell_size);
void update_grid(grid *g);

#endif