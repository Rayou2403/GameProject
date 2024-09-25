#include "render.h"
#include "level.h"
#include <SDL2/SDL.h>

void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *rightPlayerTexture, SDL_Texture *leftPlayerTexture, int playerFrame, Player player, int facingLeft) {
    int tileSize = 32;  // Each tile is 32x32 pixels

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            SDL_Rect tileRect = {x * tileSize, y * tileSize, tileSize, tileSize};

            // Render green block for '#'
            if (level.tiles[y][x] == '#') {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color
                SDL_RenderFillRect(renderer, &tileRect);
            } else if (level.tiles[y][x] == '@') {
                // Render the player using the correct sprite sheet based on direction
                SDL_Rect srcRect = {playerFrame * 64, 0, 64, 64};  // Original player sprite frame (64x64)
                int scaleFactor = 10;
                SDL_Rect destRect = {x * tileSize, y * tileSize, tileSize*scaleFactor, tileSize*scaleFactor};  // Scale player

                if (facingLeft) {
                    SDL_RenderCopy(renderer, leftPlayerTexture, &srcRect, &destRect);  // Use left-facing texture
                } else {
                    SDL_RenderCopy(renderer, rightPlayerTexture, &srcRect, &destRect);  // Use right-facing texture
                }
            }
        }
    }
}
