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
const int STARTING_BACKGROUND_X = -400; // Specify the starting position of the background in X coordinate
const int STARTING_BACKGROUND_Y = -848; // Specify the starting position of the background in Y coordinate
const int CHARACTER_START_X = 160;
const int CHARACTER_START_Y = 128;

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* backgroundTexture;
        SDL_Texture* characterTexture;
        SDL_Rect backgroundRect;
        SDL_Rect characterRect;
        int backgroundWidth; // Declare background width
        int backgroundHeight; // Declare background height

        void loadTextures();
        
    public:
        Game();
        ~Game();
        void run();
};