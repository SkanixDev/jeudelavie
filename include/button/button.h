#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button_types.h"

void draw_button(SDL_Renderer *renderer, button *btn);

#endif