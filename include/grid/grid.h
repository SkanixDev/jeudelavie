#ifndef GRID_H
#define GRID_H

#include "grid_types.h"
#include <SDL2/SDL.h>

int init_grid(grid *g, int height, int width);
int free_grid(grid *g);
int print_grid(grid *g);

int draw_grid(grid *g, SDL_Renderer *renderer, int x, int y, int cell_size);
int update_grid(grid *g);

#endif