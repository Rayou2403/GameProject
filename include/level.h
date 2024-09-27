#ifndef LEVEL_H
#define LEVEL_H

#define WIDTH 140
#define HEIGHT 31

// Structure to represent the level
typedef struct {
    char tiles[HEIGHT][WIDTH];
} Level;


Level generateRandomLevel(); // Function to generate a random level
void saveLevelToFile(Level level, const char *filename); // Function to save the level to a file
Level loadLevelFromFile(const char *filename); // Function to load a level from a file

void printLevel(Level level); // (TESTING) Function to print the level to the console (TESTING)
#endif // LEVEL_H
