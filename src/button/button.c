#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "button/button_types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void draw_button(SDL_Renderer *renderer, button *btn)
{
    SDL_Rect rect = {btn->x, btn->y, btn->w, btn->h};
    if (btn->is_filled)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
    TTF_Font *font = TTF_OpenFont("bin/reppixel.ttf", 15);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, btn->text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect text_rect = {btn->x + btn->w / 2 - 10, btn->y + btn->h / 2 - 10, 20, 20};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}