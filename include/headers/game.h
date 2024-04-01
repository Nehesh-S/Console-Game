#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 320;
const int WINDOW_HEIGHT = 240;
const int CHARACTER_WIDTH = 16;
const int CHARACTER_HEIGHT = 32;
const int MOVE_DELAY_MS = 100;
const int SCROLL_LIMIT_X = 64;
const int SCROLL_LIMIT_Y = 64;
const int STARTING_BACKGROUND_X = -400;
const int STARTING_BACKGROUND_Y = -848;
const int CHARACTER_START_X = 160;
const int CHARACTER_START_Y = 128;

struct BoundingBox {
    int x, y, w, h;
};

class Game {
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* backgroundTexture;
        SDL_Texture* characterTexture;
        SDL_Rect backgroundRect;
        SDL_Rect characterRect;
        int backgroundWidth;
        int backgroundHeight;
        std::vector<BoundingBox> boundingBoxes;

        void loadTextures();
        void addBoundingBoxes();
        bool isCharacterInBoundingBox(int x, int y);
        
    public:
        Game();
        ~Game();
        void run();
};