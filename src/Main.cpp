#include <game.h>

int main(int argc, char* argv[]) {
    
    int screenWidth = 1024;
    int screenHeight = 600;
    
    Game game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    SDL_Texture* frog = game.loadTexture("res/gfx/building_small.jpg");

    while (game.gameState != GameState::EXIT) {
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type) {
        case SDL_QUIT:
            game.gameState = GameState::EXIT;
            break;
        }

        game.render(frog);
        game.run();
    }

    return 0;
}