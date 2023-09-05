#ifndef TEXT_H
#define TEXT_H

#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"


SDL_Texture* create_texture(SDL_Renderer* renderer, TTF_Font* font, char text[], SDL_Color);

void render_texture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect button_rect);

#endif
