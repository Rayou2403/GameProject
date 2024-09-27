#include "level.h"
#include "render.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define WIDTH_WINDOW 59.5
#define HEIGHT_WINDOW 32.5
// Define the camera size based on your window size
int cameraWidth = (int)(WIDTH_WINDOW * 32);   // Width of the camera in pixels
int cameraHeight = (int)(HEIGHT_WINDOW * 32); // Height of the camera in pixels

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image for PNG loading
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow(
        "Ascend", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED - 1,  // Adjust vertical centering as needed
        (int)(WIDTH_WINDOW * 32),  // Convert width to integer
        (int)(HEIGHT_WINDOW * 32), // Convert height to integer
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Load the level from the text file
    Level level = loadLevelFromFile("levels/saved_level.txt");

    // Load player sprite sheets (right and left)
    SDL_Surface *rightPlayerSurface = IMG_Load("assets/Player_Right_Ascend.png");  // Right-facing sprite sheet
    SDL_Surface *leftPlayerSurface = IMG_Load("assets/Player_Left_Ascend.png");    // Left-facing sprite sheet
    SDL_Surface *groundSurface = IMG_Load("assets/Ground_Ascend.png");
    if (!rightPlayerSurface || !leftPlayerSurface || !groundSurface) {
        printf("Error loading player/ground sprites: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *rightPlayerTexture = SDL_CreateTextureFromSurface(renderer, rightPlayerSurface);
    SDL_Texture *leftPlayerTexture = SDL_CreateTextureFromSurface(renderer, leftPlayerSurface);
    SDL_Texture *groundTexture = SDL_CreateTextureFromSurface(renderer, groundSurface);
    SDL_FreeSurface(rightPlayerSurface);
    SDL_FreeSurface(leftPlayerSurface);
    SDL_FreeSurface(groundSurface);

    if (!rightPlayerTexture || !leftPlayerTexture || !groundTexture) {
        printf("Error creating player/ground textures: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }



    // saveLevelToFile(generateRandomLevel(),"levels/saved_level.txt");

    // Initialize the player
    Player player = initPlayer(&level);
    int playerFrame = 0;  // Current frame for sprite animation
    int facingLeft = 0;  // Track whether the player is facing left (1) or right (0)
    int frameCounter = 0;  // Initialize the frame counter


    int cameraX = 0;
    int cameraY = 0;
    int tileSize = 32; // Tile Size

    // Main loop variables
    int running = 1;
    SDL_Event event;

    // SDL's keyboard state array
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }   
        // printf("position x : %f\n position y : %f\n\n",player.x,player.y);
        // Move the player based on keyboard input
        movePlayer(&level, &player, event, keyboardState, &playerFrame, &facingLeft,&frameCounter);

        // Apply physics to the player (velocity changes)
        applyPhysics(&player, &level);

        // Update camera position based on player
        updateCamera(&player, &cameraX, &cameraY,tileSize);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Render the level and player
        renderLevel(renderer, level, rightPlayerTexture, leftPlayerTexture, groundTexture,playerFrame, player, facingLeft,cameraX,cameraY);

        // Present the renderer
        SDL_RenderPresent(renderer);
    
    }

    // Clean up
    SDL_DestroyTexture(rightPlayerTexture);
    SDL_DestroyTexture(leftPlayerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();  // Quit SDL_image
    SDL_Quit();

    return 0;
}
