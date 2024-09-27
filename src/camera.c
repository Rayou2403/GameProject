#include "camera.h"
#include "level.h"  // Assuming level size (WIDTH, HEIGHT) is defined here

// Define your camera size variables (e.g., cameraWidth, cameraHeight)
extern int cameraWidth;
extern int cameraHeight;

void updateCamera(Player *player, int *cameraX, int *cameraY, int tileSize) {
    // Half the screen size to keep player centered
    int halfCameraWidth = cameraWidth / 2;
    int halfCameraHeight = cameraHeight / 2;

    // Center the camera around the player
    *cameraX = (player->x * tileSize) - halfCameraWidth;
    *cameraY = (player->y * tileSize) - halfCameraHeight;

    // Ensure the camera doesn't go out of level bounds
    if (*cameraX < 0) *cameraX = 0;  // Left boundary
    if (*cameraY < 0) *cameraY = 0;  // Top boundary
    if (*cameraX > (WIDTH * tileSize - cameraWidth)) *cameraX = (WIDTH * tileSize - cameraWidth);  // Right boundary
    if (*cameraY > (HEIGHT * tileSize - cameraHeight)) *cameraY = (HEIGHT * tileSize - cameraHeight); // Bottom boundary
}
