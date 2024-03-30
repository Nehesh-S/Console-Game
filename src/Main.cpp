#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int WINDOW_WIDTH = 320;
const int WINDOW_HEIGHT = 240;
const int CHARACTER_WIDTH = 16;
const int CHARACTER_HEIGHT = 32;
const int MOVE_DELAY_MS = 100; // Delay in milliseconds for each movement
const int SCROLL_LIMIT_X = 64; // The limit for sprite movement before background scrolling starts (in pixels)
const int SCROLL_LIMIT_Y = 64;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Simple Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load background image
    SDL_Surface* backgroundSurface = IMG_Load("res/background/forest.png");
    if (!backgroundSurface) {
        std::cerr << "Failed to load background image: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Load character sprite image
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_up.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);

    // Get the dimensions of the background image
    int backgroundWidth, backgroundHeight;
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);

    // Position the background to allow overflow
    SDL_Rect backgroundRect = { -(backgroundWidth - WINDOW_WIDTH) / 2, -(backgroundHeight - WINDOW_HEIGHT) / 2, backgroundWidth, backgroundHeight }; // Background position and size
    SDL_Rect characterRect = { 16*9, 16*8, CHARACTER_WIDTH, CHARACTER_HEIGHT }; // Initial position and size of the character sprite

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            if (characterRect.x > 0 || backgroundRect.x < 0) {
                if (characterRect.x > SCROLL_LIMIT_X || backgroundRect.x >= 0) {
                    characterRect.x -= 16; // Move character left
                }
                else {
                    if (backgroundRect.x < 0) {
                        backgroundRect.x += 16; // Move background right to simulate larger map
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH || backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH - SCROLL_LIMIT_X || backgroundRect.x + backgroundRect.w <= WINDOW_WIDTH) {
                    characterRect.x += 16; // Move character right
                }
                else {
                    if (backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                        backgroundRect.x -= 16; // Move background left to simulate larger map
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            if (characterRect.y > 0 || backgroundRect.y < 0) {
                if (characterRect.y > SCROLL_LIMIT_Y || backgroundRect.y >= 0) {
                    characterRect.y -= 16; // Move character up
                }
                else {
                    if (backgroundRect.y < 0) {
                        backgroundRect.y += 16; // Move background down to simulate larger map
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT || backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT - SCROLL_LIMIT_Y || backgroundRect.y + backgroundRect.h <= WINDOW_HEIGHT) {
                    characterRect.y += 16; // Move character down
                }
                else {
                    if (backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                        backgroundRect.y -= 16; // Move background up to simulate larger map
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect); // Render background
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // Render character
        SDL_RenderPresent(renderer); // Present renderer
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
