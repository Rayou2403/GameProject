#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include <SDL2/SDL.h>

// Define the Player structure
typedef struct {
    int x;  // Player's X position (column)
    int y;  // Player's Y position (row)
} Player;


Player initPlayer(Level *level); // Function to initialize the player

void movePlayer(Level *level, Player *player, SDL_Event event, int *playerFrame, int *facingLeft); // Function to move the player based on keyboard input

#endif // PLAYER_H
