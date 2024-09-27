#include "level.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Function to generate a random level
Level generateRandomLevel() {
    Level level;
    // srand(time(NULL)); // Initialize random seed

    // Initialize the entire level with empty space
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            level.tiles[y][x] = '.'; // Empty space
        }
    }

    // Set walls on the left and right borders
    for (int y = 0; y < HEIGHT; y++) {
        level.tiles[y][0] = '|';          // Left wall
        level.tiles[y][WIDTH - 1] = '|';  // Right wall
    }

    // Set ground at the bottom row
    for (int x = 0; x < WIDTH; x++) {
        level.tiles[HEIGHT - 1][x] = '#'; // Ground tile
    }

    // Place player start position (`@`)
    level.tiles[HEIGHT - 3][1] = '@';  // Second to last row, second column

    // // You can still randomize the rest of the level as needed
    // for (int y = 0; y < HEIGHT - 1; y++) { // Avoid ground and borders
    //     for (int x = 1; x < WIDTH - 1; x++) { // Avoid left and right walls
    //         if (rand() % 10 < 3) {
    //             level.tiles[y][x] = '#'; // Random ground tiles
    //         }
    //     }
    // }

    return level;
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

