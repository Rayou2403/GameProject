#include "player.h"
#include <SDL2/SDL.h>



// Function to initialize the player
Player initPlayer(Level *level) {
    Player player;

    // Find the '@' character in the grid and set the player's starting position
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (level->tiles[y][x] == '@') {
                player.x = x;
                player.y = y;
                player.velX = 0;  // Start with no horizontal velocity
                player.grounded = 1;  // Assume player starts on the ground
                return player;
            }
        }
    }

    // If '@' is not found, default to (0, 0) position
    player.x = 0;
    player.y = 0;
    player.velX = 0;
    player.grounded = 1;
    return player;
}


// Handle keyboard input for moving right and left
void movePlayer(Level *level, Player *player, SDL_Event event, const Uint8 *keyboardState, int *playerFrame, int *facingLeft, int *frameCounter) {
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        if (player->velX < MAX_SPEED) {
            player->velX += ACCELERATION;
        }
        *facingLeft = 0;

        // Increment frame counter
        (*frameCounter)++;
        // Change frame only if the delay is reached
        if (*frameCounter >= FRAME_DELAY) {
            *playerFrame = (*playerFrame + 1) % 13;  // Update animation frame
            *frameCounter = 0;  // Reset counter
        }
    } 
    else if (keyboardState[SDL_SCANCODE_LEFT]) {
        if (player->velX > -MAX_SPEED) {
            player->velX -= ACCELERATION;
        }
        *facingLeft = 1;

        // Increment frame counter
        (*frameCounter)++;
        // Change frame only if the delay is reached
        if (*frameCounter >= FRAME_DELAY) {
            *playerFrame = (*playerFrame + 1) % 13;  // Update animation frame
            *frameCounter = 0;  // Reset counter
        }
    } 
    else {
        if (player->velX > 0) {
            player->velX -= FRICTION;
            if (player->velX < 0) player->velX = 0;
        } else if (player->velX < 0) {
            player->velX += FRICTION;
            if (player->velX > 0) player->velX = 0;
        }
    }
}

// Apply physics to update the player's position smoothly
void applyPhysics(Player *player, Level *level) {
    int tileSize = 32;  // Tile size without scaling
    int scaleFactor = 10;  // Player scale factor
    int playerSize = tileSize * scaleFactor;  // Player's size in pixels after scaling

    // Calculate the player's tile position
    int tileX = player->x / tileSize;
    int tileY = player->y / tileSize;

    // Calculate the player's tile width and height (how many tiles the player occupies)
    int playerTileWidth = (playerSize / tileSize);
    int playerTileHeight = (playerSize / tileSize);

    // Assume the player is not grounded
    int isGrounded = 0;

    
    // Horizontal collisions
    if (player->velX > 0) {  // Moving right
        int rightTileX = (player->x + playerSize) / tileSize;  // Tile to the right of the player

        // Check for collision with ground tiles to the right
        for (int i = 0; i <= playerTileHeight; i++) {
            if (rightTileX < WIDTH && level->tiles[tileY + i][rightTileX] == '#') {
                player->velX = 0;  // Stop horizontal movement
                player->x = rightTileX * tileSize - playerSize;  // Snap player to the left edge of the tile
                break;
            }
        }
    } else if (player->velX < 0) {  // Moving left
        int leftTileX = (player->x - 1) / tileSize;  // Tile to the left of the player

        // Check for collision with ground tiles to the left
        for (int i = 0; i <= playerTileHeight; i++) {
            if (leftTileX >= 0 && level->tiles[tileY + i][leftTileX] == '#') {
                player->velX = 0;  // Stop horizontal movement
                player->x = (leftTileX + 1) * tileSize;  // Snap player to the right edge of the tile
                break;
            }
        }
    }

    // Vertical collision check for ground (falling down)
    int bottomTileY = (player->y + playerSize) / tileSize;  // Tile just below the player
    for (int i = 0; i <= playerTileWidth; i++) {
        // Check a vertical threshold for being "grounded"
        int checkY = bottomTileY;
        // Loop until you find a `#` tile within a few tiles below the player
        while (checkY < HEIGHT && checkY < bottomTileY + scaleFactor / 2) {
            if (level->tiles[checkY][tileX + i] == '#') {
                isGrounded = 1;  // Player is considered grounded
                break;
            }
            checkY++;
        }
    }

    // Apply velocity to the player position after collision checks
    player->x += player->velX;
    player->y += player->velY;

    // Ensure player stays within level boundaries
    if (player->x < 0) player->x = 0;
    if (player->x > (WIDTH - playerTileWidth) * tileSize) player->x = (WIDTH - playerTileWidth) * tileSize;
    if (player->y < 0) player->y = 0;
    if (player->y > (HEIGHT - playerTileHeight) * tileSize) player->y = (HEIGHT - playerTileHeight) * tileSize;
}