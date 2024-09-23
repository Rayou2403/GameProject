#ifndef RENDER_H
#define RENDER_H

#include "level.h"
#include <SDL2/SDL.h>

void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *ground, SDL_Texture *player); // Function declaration for rendering the level

#endif // RENDER_H
