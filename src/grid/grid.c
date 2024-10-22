#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid_types.h"
#include <SDL2/SDL.h>

int init_grid(grid *g, int width, int height)
{
    srand(time(NULL));
    g->width = width;
    g->height = height;
    g->cells = (cell **)malloc(sizeof(cell *) * width);
    for (int i = 0; i < width; i++)
    {
        g->cells[i] = (cell *)malloc(sizeof(cell) * height);
        for (int j = 0; j < height; j++)
        {
            cell c = {i, j, rand() % 2, 0};
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

int draw_grid(grid *g, SDL_Renderer *renderer, int x, int y, int cell_size)
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
            SDL_Rect r = {x + i * cell_size, y + j * cell_size, cell_size, cell_size};
            SDL_RenderFillRect(renderer, &r);
        }
    }
    return 0;
}

int count_neighbors(grid *g)
{
    for (int i = 0; i < g->height; i++)
    {
        for (int j = 0; j < g->width; j++)
        {
            int count_cell = 0;
            // chq elmt
            for (int x_cell = -1; x_cell <= 1; x_cell++)
            {
                for (int y_cell = -1; y_cell <= 1; y_cell++)
                {
                    if (x_cell == 0 && y_cell == 0)
                        continue;

                    int neighbor_x = i + x_cell;
                    int neighbor_y = j + y_cell;

                    if (neighbor_x < 0 || neighbor_x >= g->height || neighbor_y < 0 || neighbor_y >= g->width)
                        continue;

                    g->cells[neighbor_x][neighbor_y].state == 1 ? count_cell++ : count_cell;
                }
            }
            g->cells[i][j].neighbors = count_cell;
        }
    }
    return 0;
}

int update_grid(grid *g)
{
    count_neighbors(g);
    for (int i = 0; i < g->height; i++)
    {
        for (int j = 0; j < g->width; j++)
        {
            if (g->cells[i][j].neighbors == 3)
            {
                g->cells[i][j].state = 1;
            }
            else if (g->cells[i][j].neighbors < 2 || g->cells[i][j].neighbors > 3)
            {
                g->cells[i][j].state = 0;
            }
        }
    }
    return 0;
}