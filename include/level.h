#ifndef LEVEL_H
#define LEVEL_H

#define WIDTH 50
#define HEIGHT 20

// Structure to represent the level
typedef struct {
    char tiles[HEIGHT][WIDTH];
} Level;


Level generateRandomLevel();
void printLevel(Level level);
#endif // LEVEL_H
