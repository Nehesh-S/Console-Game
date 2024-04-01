#include "game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Simple Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    loadTextures();
    backgroundRect = { STARTING_BACKGROUND_X, STARTING_BACKGROUND_Y, backgroundWidth, backgroundHeight }; // Set the background size to the loaded image size
    characterRect = { CHARACTER_START_X, CHARACTER_START_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT };

    addBoundingBoxes();
}

Game::~Game() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT] && !isCharacterInBoundingBox(characterRect.x - 16, characterRect.y)) {
            if (characterRect.x > 0 || backgroundRect.x < 0) {
                if (characterRect.x > SCROLL_LIMIT_X || backgroundRect.x >= 0) {
                    characterRect.x -= 16; // Move character left
                }
                else {
                    if (backgroundRect.x < 0) {
                        backgroundRect.x += 16; // Move background right to simulate larger map
                    }
                    for (auto& bb : boundingBoxes) {
                        bb.x += 16;
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT] && !isCharacterInBoundingBox(characterRect.x + 16, characterRect.y)) {
            if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH || backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH - SCROLL_LIMIT_X || backgroundRect.x + backgroundRect.w <= WINDOW_WIDTH) {
                    characterRect.x += 16; // Move character right
                }
                else {
                    if (backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                        backgroundRect.x -= 16; // Move background left to simulate larger map
                    }
                    for (auto& bb : boundingBoxes) {
                        bb.x -= 16;
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_UP] && !isCharacterInBoundingBox(characterRect.x, characterRect.y - 16)) {
            if (characterRect.y > 0 || backgroundRect.y < 0) {
                if (characterRect.y > SCROLL_LIMIT_Y || backgroundRect.y >= 0) {
                    characterRect.y -= 16; // Move character up
                }
                else {
                    if (backgroundRect.y < 0) {
                        backgroundRect.y += 16; // Move background down to simulate larger map
                    }
                    for (auto& bb : boundingBoxes) {
                        bb.y += 16;
                    }
                }
                SDL_Delay(MOVE_DELAY_MS);
            }
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN] && !isCharacterInBoundingBox(characterRect.x, characterRect.y + 16)) {
            if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT || backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT - SCROLL_LIMIT_Y || backgroundRect.y + backgroundRect.h <= WINDOW_HEIGHT) {
                    characterRect.y += 16; // Move character down
                }
                else {
                    if (backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                        backgroundRect.y -= 16; // Move background up to simulate larger map
                    }
                    for (auto& bb : boundingBoxes) {
                        bb.y -= 16;
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
}

void Game::loadTextures() {
    // Load background image
    SDL_Surface* backgroundSurface = IMG_Load("res/background/forest.png");
    if (!backgroundSurface) {
        std::cerr << "Failed to load background image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Load character sprite image
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_up.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);

    // Get the dimensions of the background image
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);
}

bool Game::isCharacterInBoundingBox(int x, int y) {
    // Check if the character is within any of the bounding boxes
    for (const auto& bb : boundingBoxes) {
        if (x < bb.x + bb.w && x + CHARACTER_WIDTH > bb.x && y < bb.y + bb.h && y + CHARACTER_HEIGHT > bb.y) {
            return true; // Character is in bounding box
        }
    }
    return false; // Character is not in any bounding box
}

void Game::addBoundingBoxes() {
    BoundingBox bb1 = { STARTING_BACKGROUND_X + 0, STARTING_BACKGROUND_Y + 0, 144, 1104 };
    // topleft x, topleft y, width, height
    boundingBoxes.push_back(bb1);
}