#include "level.h"
#include "render.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

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
    SDL_Window *window = SDL_CreateWindow("Level Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * 32, HEIGHT * 32, SDL_WINDOW_SHOWN);
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

    if (!rightPlayerSurface || !leftPlayerSurface) {
        printf("Error loading player sprites: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *rightPlayerTexture = SDL_CreateTextureFromSurface(renderer, rightPlayerSurface);
    SDL_Texture *leftPlayerTexture = SDL_CreateTextureFromSurface(renderer, leftPlayerSurface);
    SDL_FreeSurface(rightPlayerSurface);
    SDL_FreeSurface(leftPlayerSurface);

    if (!rightPlayerTexture || !leftPlayerTexture) {
        printf("Error creating player textures: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize the player
    Player player = initPlayer(&level);
    int playerFrame = 0;  // Current frame for sprite animation
    int facingLeft = 0;  // Track whether the player is facing left (1) or right (0)

    // Main loop variables
    int running = 1;
    SDL_Event event;

    // Main loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            // Move the player based on keyboard input and update direction
            movePlayer(&level, &player, event, &playerFrame, &facingLeft);
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Render the level and player
        renderLevel(renderer, level, rightPlayerTexture, leftPlayerTexture, playerFrame, player, facingLeft);

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
