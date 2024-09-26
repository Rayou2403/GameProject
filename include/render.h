#ifndef RENDER_H
#define RENDER_H

#include "level.h"
#include "player.h"
#include <SDL2/SDL.h>


void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *rightPlayerTexture, SDL_Texture *leftPlayerTexture, SDL_Texture *groundTexture,int playerFrame, Player player, int facingLeft); // Function declaration for rendering the level

#endif // RENDER_H
