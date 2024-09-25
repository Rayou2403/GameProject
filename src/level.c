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

    // Randomize the end-of-level '$' position
    int endX, endY;

    // Ensure the end '$' is not placed at the player's starting position
    do {
        endX = rand() % WIDTH;
        endY = rand() % HEIGHT;
    } while (endX == 0 && endY == HEIGHT - 2);  // Prevent it from overlapping with '@'

    level.tiles[endY][endX] = '$';  // Place the end of the level

    return(level);
}

// Function to save the level to a file
void saveLevelToFile(Level level, const char *filename) {
    FILE *file = fopen(filename,"w");
    if (!file) {
        printf("Erro : Unable to open file %s for writing\n",filename);
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fputc(level.tiles[y][x],file); // Write each tile to the file
        }
        fputc('\n',file); // Add a new line at the end of each row
    }

    fclose(file);
    printf("Level saved to %s\n", filename);
}

// Function to load a level from a file
Level loadLevelFromFile(const char *filename) {
    Level level;
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Unable to open file %s for reading\n", filename);
        exit(1);  // Exit on error (you can handle this better in a larger project)
    }

    int y = 0;
    char line[WIDTH + 2];  // +2 for newline and null terminator
    while (fgets(line, sizeof(line), file) && y < HEIGHT) {
        for (int x = 0; x < WIDTH; x++) {
            if (line[x] == '\n') break;  // Skip newline characters
            level.tiles[y][x] = line[x];  // Copy the tile character
        }
        y++;
    }

    fclose(file);
    return level;
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

