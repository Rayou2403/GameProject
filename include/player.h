#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include <SDL2/SDL.h>

// Physics of the game for moving
#define ACCELERATION 0.01f
#define MAX_SPEED 0.05f
#define FRICTION 0.0003f
#define FRAME_DELAY 32 

typedef struct {
    float x, y;          // Player's position on the grid (tile-based)
    float velX,velY;        // Horizontal velocity (smooth movement)
    int grounded;      // Whether the player is on the ground
} Player;

// Initializes the player at a given position in the level
Player initPlayer(Level *level);

// Moves the player based on keyboard input (uses continuous input)
void movePlayer(Level *level, Player *player, SDL_Event event, const Uint8 *keyboardState, int *playerFrame, int *facingLeft, int *frameCounter);

// Updates the player's position based on velocity and friction
void applyPhysics(Player *player, Level *level);

#endif
