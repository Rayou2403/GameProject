#include "level.h"
#include <SDL2/SDL.h>

void renderLevel(SDL_Renderer *renderer, Level level, SDL_Texture *ground, SDL_Texture *player) {
    int tileSize = 32;  // Size of each tile in pixels

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            SDL_Rect dest = {x * tileSize, y * tileSize, tileSize, tileSize};

            switch (level.tiles[y][x]) {
                case '#':
                    SDL_RenderCopy(renderer, ground, NULL, &dest);
                    break;
                case '@':
                    SDL_RenderCopy(renderer, player, NULL, &dest);
                    break;
                // Add other cases for different tile types (if needed)
                default:
                    break;  // Empty space ('.')
            }
        }
    }
}
