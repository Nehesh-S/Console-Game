#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int CHARACTER_WIDTH = 32;
const int CHARACTER_HEIGHT = 64;
const int MOVE_DELAY_MS = 100;
const int SCROLL_LIMIT_X = 128;
const int SCROLL_LIMIT_Y = 128;
const int STARTING_BACKGROUND_X = -800;
const int STARTING_BACKGROUND_Y = -1696;
const int CHARACTER_START_X = 320;
const int CHARACTER_START_Y = 256;

const int TREE_WIDTH = 96;
const int TREE_HEIGHT = 64;
const int GRASS_WIDTH = 32;
const int GRASS_HEIGHT = 32;
const int MAP_WIDTH = 2112;
const int MAP_HEIGHT = 2208;

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

        bool left = false;
        bool right = false;
        bool down = false;
        bool up = false;

        void loadTextures();
        void addBoundingBoxes();
        bool isCharacterInBoundingBox(int x, int y);
        void spriteup();
        void spritedown();
        void spriteleft();
        void spriteright();
        
    public:
        Game();
        ~Game();
        void run();
};