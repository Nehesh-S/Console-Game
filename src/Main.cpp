#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

const int WINDOW_WIDTH = 320;
const int WINDOW_HEIGHT = 240;
const int CHARACTER_WIDTH = 16;
const int CHARACTER_HEIGHT = 32;
const int MOVE_DELAY_MS = 100; // Delay in milliseconds for each movement

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

    SDL_Rect backgroundRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT }; // Background position and size
    SDL_Rect characterRect = { 0, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT }; // Initial position and size of the character sprite

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
            if (characterRect.x > 0) {
                characterRect.x -= 16; // Move character left
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH) {
                characterRect.x += 16; // Move character right
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            if (characterRect.y > 0) {
                characterRect.y -= 16; // Move character up
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT) {
                characterRect.y += 16; // Move character down
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
