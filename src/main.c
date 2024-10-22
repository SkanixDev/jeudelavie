#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "grid/grid.h"
#include "button/button.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

// parametres de la grille
enum game_state
{
    PAUSE,
    PLAY
};

#define GRID_WIDTH 150
#define GRID_HEIGHT 120

#define CELL_SIZE 5

#define TIME_PER_GEN 0

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

    if (!TTF_WasInit() && TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > Error SDL_TTF");
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Default parameters
    SDL_SetWindowTitle(pWindow, "Game of Life");
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_ADD);
    // -> manage font
    TTF_Font *pixel_font = TTF_OpenFont("bin/reppixel.ttf", 15);
    if (!pixel_font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", TTF_GetError());
        return EXIT_FAILURE;
    }

    SDL_Color pixel_color = {255, 255, 255};
    SDL_Surface *pixel_surface = TTF_RenderText_Solid(pixel_font, "GAME OF LIFE", pixel_color);
    if (!pixel_surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create surface: %s", TTF_GetError());
        TTF_CloseFont(pixel_font);
        return EXIT_FAILURE;
    }

    SDL_Texture *pixel_texture = SDL_CreateTextureFromSurface(pRenderer, pixel_surface);
    if (!pixel_texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(pixel_surface);
        TTF_CloseFont(pixel_font);
        return EXIT_FAILURE;
    }
    // Gameloop
    bool isRunning = true;
    enum game_state game_state = PAUSE;
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

        draw_grid(&g, pRenderer, WINDOW_WIDTH - (GRID_WIDTH * CELL_SIZE), 0, CELL_SIZE);

        if (game_state == PLAY)
        {
            update_grid(&g);
        }
        else
        {
            // draw button
            button btn = {10, 10, 100, 50, "PLAY", 0, 1};
            draw_button(pRenderer, &btn);
        }

        // show text
        SDL_Rect dstrect = {10, 10, pixel_surface->w, pixel_surface->h};
        SDL_RenderCopy(pRenderer, pixel_texture, NULL, &dstrect);

        SDL_RenderPresent(pRenderer); // update
        SDL_Delay(TIME_PER_GEN);
    }

    // end
    free_grid(&g);
    SDL_FreeSurface(pixel_surface);    // close pixel font
    SDL_DestroyTexture(pixel_texture); // close pixel font
    TTF_CloseFont(pixel_font);         // close pixel font
    TTF_Quit();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}