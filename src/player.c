#include "player.h"
#include <SDL2/SDL.h>

// Initialize the player and set the starting position
Player initPlayer(Level *level) {
    Player player;

    // Find the '@' character in the grid and set the player's starting position
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (level->tiles[y][x] == '@') {
                player.x = x;
                player.y = y;
                return player;  // Player initialized
            }
        }
    }

    // Default starting position if '@' is not found
    player.x = 0;
    player.y = 0;
    return player;
}

// Handle keyboard input for moving right and left
void movePlayer(Level *level, Player *player, SDL_Event event, int *playerFrame, int *facingLeft) {
    int newX = player->x;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RIGHT:
                // Move right
                if (player->x < WIDTH - 1 && level->tiles[player->y][player->x + 1] != '#') {
                    newX++;  // Move right
                    (*playerFrame) = ((*playerFrame) + 1) % 13;  // Update the player frame (13 frames in sprite sheet)
                    *facingLeft = 0;  // Player is facing right

                    // Update the grid: Set the old position to empty space
                    level->tiles[player->y][player->x] = '.';

                    // Update the player's position
                    player->x = newX;

                    // Set the new position in the grid
                    level->tiles[player->y][player->x] = '@';
                }
                break;

            case SDLK_LEFT:
                // Move left
                if (player->x > 0 && level->tiles[player->y][player->x - 1] != '#') {
                    newX--;  // Move left
                    (*playerFrame) = ((*playerFrame) + 1) % 13;  // Update the player frame (13 frames in sprite sheet)
                    *facingLeft = 1;  // Player is facing left

                    // Update the grid: Set the old position to empty space
                    level->tiles[player->y][player->x] = '.';

                    // Update the player's position
                    player->x = newX;

                    // Set the new position in the grid
                    level->tiles[player->y][player->x] = '@';
                }
                break;
        }
    }
}
