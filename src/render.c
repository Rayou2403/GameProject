#include "render.h"
#include "level.h"
#include <SDL2/SDL.h>
#include <time.h>

 // Function declaration for rendering the level
void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *rightPlayerTexture, SDL_Texture *leftPlayerTexture, SDL_Texture *groundTexture, int playerFrame, Player player, int facingLeft) {
    int tileSize = 32;  // Each tile is 32x32 pixels

    // Define scale factors for ground and player
    int groundScaleFactor = 10;  // Adjust this to scale the ground
    int playerScaleFactor = 10;  // Scale factor for the player

    // Calculate offsets for centering sprites after scaling
    int groundOffset = (groundScaleFactor - 1) * tileSize / 2;
    int playerOffset = (playerScaleFactor - 1) * tileSize / 2;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Calculate the position and size for ground tile, centered
            SDL_Rect tileRect = {
                x * tileSize  - groundOffset,
                y * tileSize  - groundOffset,
                tileSize * groundScaleFactor,
                tileSize * groundScaleFactor
            };

            // Render the ground texture for '#'
            if (level.tiles[y][x] == '#') {
                // Apply visual pattern: render only 3rd tile in x direction
                if (x % 3 ==0)
                {
                    SDL_RenderCopy(renderer, groundTexture, NULL, &tileRect);
                }
               
            } else if (level.tiles[y][x] == '@') {
                // Calculate the source and destination rectangles for the player
                SDL_Rect srcRect = {playerFrame * 64, 0, 64, 64};  // Original player sprite frame (64x64)
                
                SDL_Rect destRect = {
                    player.x * tileSize - playerOffset,
                    player.y * tileSize - playerOffset,
                    tileSize * playerScaleFactor,
                    tileSize * playerScaleFactor
                };

                // Render the player using the correct sprite sheet based on direction
                if (facingLeft) {
                    SDL_RenderCopy(renderer, leftPlayerTexture, &srcRect, &destRect);  // Use left-facing texture
                } else {
                    SDL_RenderCopy(renderer, rightPlayerTexture, &srcRect, &destRect);  // Use right-facing texture
                }
            }
        }
    }
}


