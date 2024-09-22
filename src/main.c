#include "level.h"

int main() {
    // Generate a random level
    Level level = generateRandomLevel();

    // Print the generated level to the console (for testing)
    printLevel(level);

    return 0;
}