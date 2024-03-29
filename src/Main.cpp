#include <game.h>

int main(int argc, char* argv[]) {
    
    int _screenWidth = 1024;
    int _screenHeight = 600;
    
    Game game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);
    game.run();

    return 0;
}