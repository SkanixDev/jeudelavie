#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "grid/grid.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// parametres de la grille
#define GRID_WIDTH 100
#define GRID_HEIGHT 100

#define CELL_SIZE 5

#define TIME_PER_GEN 100

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *pWindow;     // ma fenêtre
    SDL_Renderer *pRenderer; // mon rendu
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Default parameters
    SDL_SetWindowTitle(pWindow, "Game of Life");
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_ADD);

    // Gameloop
    bool isRunning = true;
    SDL_Event e;

    grid g;
    init_grid(&g, GRID_WIDTH, GRID_HEIGHT);
    while (isRunning)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
        // Clear screen
        SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);

        draw_grid(&g, pRenderer, 0, 0, CELL_SIZE);
        update_grid(&g);
        SDL_Delay(TIME_PER_GEN);
        SDL_RenderPresent(pRenderer); // On mets a jour notre fenêtre
    }

    // Fin
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}