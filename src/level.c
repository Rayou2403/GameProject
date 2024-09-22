#include "level.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Function to generate a random level
Level generateRandomLevel() {
    Level level;
    srand(time(NULL)); // Initialize random seed

    // Generate random tiles 
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (rand() % 10 < 3) {
                level.tiles[y][x] = '#'; // Ground tile
            } else {
                level.tiles[y][x] = '.'; // Empty space
            }
        }
    }

    level.tiles[HEIGHT - 2][0] = '@'; // Player starting position

    return(level);
}

// (TESTING) Function to print the level to the console (TESTING)

void printLevel(Level level) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", level.tiles[y][x]);
        }
        printf("\n");
    }
}

