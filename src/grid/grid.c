#include <stdio.h>
#include "grid_types.h"
#include <SDL2/SDL.h>

#define CELL_SIZE 10

int init_grid(grid *g, int width, int height)
{
    g->width = width;
    g->height = height;
    g->cells = (cell **)malloc(sizeof(cell *) * width);
    for (int i = 0; i < width; i++)
    {
        g->cells[i] = (cell *)malloc(sizeof(cell) * height);
        for (int j = 0; j < height; j++)
        {
            cell c = {i, j, rand() % 2};
            g->cells[i][j] = c;
        }
    }
    return 0;
}

int free_grid(grid *g)
{
    for (int i = 0; i < g->width; i++)
    {
        free(g->cells[i]);
    }
    free(g->cells);
    return 0;
}

int print_grid(grid *g)
{
    for (int i = 0; i < g->width; i++)
    {
        for (int j = 0; j < g->height; j++)
        {
            printf("%d", g->cells[i][j].state);
        }
        printf("\n");
    }
    return 0;
}

int draw_grid(grid *g, SDL_Renderer *renderer, int x, int y)
{
    for (int i = 0; i < g->width; i++)
    {
        for (int j = 0; j < g->height; j++)
        {
            if (g->cells[i][j].state == 1)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_Rect r = {x + i * CELL_SIZE, y + j * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_RenderFillRect(renderer, &r);
        }
    }

    return 0;
}