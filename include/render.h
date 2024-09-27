#ifndef RENDER_H
#define RENDER_H

#include "level.h"
#include "player.h"
#include <SDL2/SDL.h>


void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *rightPlayerTexture, SDL_Texture *leftPlayerTexture, SDL_Texture *groundTexture, 
int playerFrame, Player player, int facingLeft, int cameraX, int cameraY); // Function declaration for rendering the level

void updateCamera(Player *player, int *cameraX, int *cameraY, int tileSize);// Function that adapt the camera to the player
#endif // RENDER_H
