#include "game.h"

Game::Game() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Console Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    loadTextures();
    spriteup();
    up = true;
    backgroundRect = { STARTING_BACKGROUND_X, STARTING_BACKGROUND_Y, backgroundWidth, backgroundHeight };
    characterRect = { CHARACTER_START_X, CHARACTER_START_Y, CHARACTER_WIDTH, CHARACTER_HEIGHT };

    addBoundingBoxes();
    addGrass();
}

Game::~Game() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    inStartScreen = true;
    isEndScreen = false;
    isLose = false;
    quit = false;

    while (inStartScreen) {
        handleStartScreenEvents();
        renderStartScreen();
    }

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        if (inStartScreen) {
            while (inStartScreen) {
                handleStartScreenEvents();
                renderStartScreen();
            }
        }

        if (isLose) {
            while (isLose) {
                handleEndScreenEvents();
                renderDefeatScreen();
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_LEFT] && !isCharacterInBoundingBox(characterRect.x - 16, characterRect.y)) {
            if (left) {
                if (characterRect.x > 0 || backgroundRect.x < 0) {
                    if (characterRect.x > SCROLL_LIMIT_X || backgroundRect.x >= 0) {
                        characterRect.x -= 32;
                    }
                    else {
                        if (backgroundRect.x < 0) {
                            backgroundRect.x += 32;
                        }
                        for (auto& bb : boundingBoxes) {
                            bb.x += 32;
                        }
                        for (auto& gb : grass) {
                            gb.x += 32;
                        }
                        victoryBox.x += 32;
                    }
                }
            }
            else {
                left = true;
                up = down = right = false;
                spriteleft();
            }
            SDL_Delay(MOVE_DELAY_MS);
        }
        if (currentKeyStates[SDL_SCANCODE_RIGHT] && !isCharacterInBoundingBox(characterRect.x + 16, characterRect.y)) {
            if (right) {
                if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH || backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                    if (characterRect.x < WINDOW_WIDTH - CHARACTER_WIDTH - SCROLL_LIMIT_X || backgroundRect.x + backgroundRect.w <= WINDOW_WIDTH) {
                        characterRect.x += 32;
                    }
                    else {
                        if (backgroundRect.x + backgroundRect.w > WINDOW_WIDTH) {
                            backgroundRect.x -= 32;
                        }
                        for (auto& bb : boundingBoxes) {
                            bb.x -= 32;
                        }
                        for (auto& gb : grass) {
                            gb.x -= 32;
                        }
                        victoryBox.x -= 32;
                    }
                }
            }
            else {
                right = true;
                up = down = left = false;
                spriteright();
            }
            SDL_Delay(MOVE_DELAY_MS);
        }
        if (currentKeyStates[SDL_SCANCODE_UP] && !isCharacterInBoundingBox(characterRect.x, characterRect.y - 32)) {
            if (up) {
                if (characterRect.y > 0 || backgroundRect.y < 0) {
                    if (characterRect.y > SCROLL_LIMIT_Y || backgroundRect.y >= 0) {
                        characterRect.y -= 32;
                    }
                    else {
                        if (backgroundRect.y < 0) {
                            backgroundRect.y += 32;
                        }
                        for (auto& bb : boundingBoxes) {
                            bb.y += 32;
                        }
                        for (auto& gb : grass) {
                            gb.y += 32;
                        }
                        victoryBox.y += 32;
                    }
                }
            }
            else {
                up = true;
                left = down = right = false;
                spriteup();
            }
            SDL_Delay(MOVE_DELAY_MS);
        }
        if (currentKeyStates[SDL_SCANCODE_DOWN] && !isCharacterInBoundingBox(characterRect.x, characterRect.y + 32)) {
            if (down) {
                if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT || backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                    if (characterRect.y < WINDOW_HEIGHT - CHARACTER_HEIGHT - SCROLL_LIMIT_Y || backgroundRect.y + backgroundRect.h <= WINDOW_HEIGHT) {
                        characterRect.y += 32;
                    }
                    else {
                        if (backgroundRect.y + backgroundRect.h > WINDOW_HEIGHT) {
                            backgroundRect.y -= 32;
                        }
                        for (auto& bb : boundingBoxes) {
                            bb.y -= 32;
                        }
                        for (auto& gb : grass) {
                            gb.y -= 32;
                        }
                        victoryBox.y -= 32;
                    }
                }
            }
            else {
                down = true;
                up = left = right = false;
                spritedown();
            }
            SDL_Delay(MOVE_DELAY_MS);
        }

        if (isVictory(characterRect.x, characterRect.y)) 
            isEndScreen = true;

        while (isEndScreen) {
            handleEndScreenEvents();
            renderEndScreen();
        }
        
        updateTimer();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect); // Render background
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect); // Render character
        SDL_RenderPresent(renderer);
        renderTimer();
    }
}

void Game::loadTextures() {
    // Load background image
    SDL_Surface* backgroundSurface = IMG_Load("res/background/forest_L.png");
    if (!backgroundSurface) {
        std::cerr << "Failed to load background image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Get the dimensions of the background image
    SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundWidth, &backgroundHeight);
}

void Game::spriteup() {
    // Load character image
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_up.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);
}

void Game::spritedown() {
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_down.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);
}

void Game::spriteleft() {
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_left.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);
}

void Game::spriteright() {
    SDL_Surface* characterSurface = IMG_Load("res/player/normal_right.png");
    if (!characterSurface) {
        std::cerr << "Failed to load character sprite image: " << SDL_GetError() << std::endl;
        exit(1);
    }
    characterTexture = SDL_CreateTextureFromSurface(renderer, characterSurface);
    SDL_FreeSurface(characterSurface);
}

bool Game::isCharacterInBoundingBox(int x, int y) {
    for (const auto& bb : boundingBoxes) {
        if (x < bb.x + bb.w && x + CHARACTER_WIDTH > bb.x && y < bb.y + bb.h && y + CHARACTER_HEIGHT > bb.y) {
            return true; // Character is in bounding box
        }
    }
    return false; // Character is not in any bounding box
}

void Game::renderStartScreen() {
    // Render the start screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_Surface* startScreenImageSurface = IMG_Load("res/start/start.png");
    if (!startScreenImageSurface) {
        std::cerr << "Failed to load start screen image: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* startScreenImageTexture = SDL_CreateTextureFromSurface(renderer, startScreenImageSurface);
    SDL_FreeSurface(startScreenImageSurface);

    SDL_Rect imageRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, startScreenImageTexture, NULL, &imageRect);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(startScreenImageTexture);
}

void Game::handleStartScreenEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            inStartScreen = false;
            return;
        } else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_RETURN) {
                inStartScreen = false;
            }
        }
    }
}

void Game::renderEndScreen() {
    // Render the end screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_Surface* endScreenImageSurface = IMG_Load("res/end/victory.png");
    if (!endScreenImageSurface) {
        std::cerr << "Failed to load end screen image: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* endScreenImageTexture = SDL_CreateTextureFromSurface(renderer, endScreenImageSurface);
    SDL_FreeSurface(endScreenImageSurface);

    SDL_Rect imageRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, endScreenImageTexture, NULL, &imageRect);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(endScreenImageTexture);
}

void Game::renderDefeatScreen() {
    // Render the loose screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    
    SDL_Surface* endScreenImageSurface = IMG_Load("res/end/defeat.jpg");
    if (!endScreenImageSurface) {
        std::cerr << "Failed to load start screen image: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* endScreenImageTexture = SDL_CreateTextureFromSurface(renderer, endScreenImageSurface);
    SDL_FreeSurface(endScreenImageSurface);

    SDL_Rect imageRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderCopy(renderer, endScreenImageTexture, NULL, &imageRect);

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(endScreenImageTexture);
}

void Game::handleEndScreenEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            isEndScreen = false;
            isLose = false;
            return;
        }
    }
}

bool Game::isVictory(int x, int y) {
    if (x < victoryBox.x + victoryBox.w && x > victoryBox.x && y < victoryBox.y + victoryBox.h && y > victoryBox.y) {
        return true;
    }
    return false;
}

void Game::updateTimer() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - gTimerStartTime >= 1000 && gTimerValue > 0) {
        gTimerValue--;
        gTimerStartTime = currentTime;
    }
    if (gTimerValue == 0) {
        isLose = true;
    }
    // std::cout << gTimerValue << std::endl;
}

void Game::renderTimer() {
    int characterWidth = 12;
    int characterHeight = 20;

    // Set the initial position
    int x = WINDOW_WIDTH - TIMER_WIDTH - 10;
    int y = 10;

    std::string timerText = std::to_string(gTimerValue);
    for (char digit : timerText) {

        std::string digitStr(1, digit);
        std::string filename = "res/numbers/" + digitStr + ".png";
        // std::cout << filename << "\n";

        SDL_Surface* digitSurface = IMG_Load(filename.c_str());
        if (digitSurface == nullptr) {
            std::cerr << "Failed to load digit surface! SDL_image Error: " << IMG_GetError() << std::endl;
            return;
        }

        SDL_Texture* digitTexture = SDL_CreateTextureFromSurface(renderer, digitSurface);
        if (digitTexture == nullptr) {
            std::cerr << "Failed to create digit texture! SDL Error: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(digitSurface);
            return;
        }

        SDL_Rect digitRect = { x, y, characterWidth, characterHeight };
        SDL_RenderCopy(renderer, digitTexture, NULL, &digitRect);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(digitTexture);
        SDL_FreeSurface(digitSurface);

        x += characterWidth;
    }
}