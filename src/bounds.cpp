#include "game.h"

const int TREE_WIDTH = 48;

void Game::addBoundingBoxes() {
    // topleft x, topleft y, width, height
    BoundingBox left_forest = { STARTING_BACKGROUND_X + 0, STARTING_BACKGROUND_Y + 0, 144, 1104 };
    boundingBoxes.push_back(left_forest);

    BoundingBox right_forest = { STARTING_BACKGROUND_X + 912, STARTING_BACKGROUND_Y + 0, 144, 1104 };
    boundingBoxes.push_back(right_forest);

    BoundingBox top_forest = { STARTING_BACKGROUND_X + 144, STARTING_BACKGROUND_Y + 0, 816, 64 };
    boundingBoxes.push_back(top_forest);

    BoundingBox bottom_forest = { STARTING_BACKGROUND_X + 144, STARTING_BACKGROUND_Y + 1008, 1056, 96 };
    boundingBoxes.push_back(bottom_forest);

    BoundingBox end = { STARTING_BACKGROUND_X + 96, STARTING_BACKGROUND_Y + 64, 176, 96 };
    boundingBoxes.push_back(end);

    BoundingBox start = { STARTING_BACKGROUND_X + 480, STARTING_BACKGROUND_Y + 1008, 176, 96 };
    boundingBoxes.push_back(start);

    BoundingBox startleft = { STARTING_BACKGROUND_X + 0, STARTING_BACKGROUND_Y + 992, 528, 16 };
    boundingBoxes.push_back(startleft);

    BoundingBox startright = { STARTING_BACKGROUND_X + 656, STARTING_BACKGROUND_Y + 992, 400, 96 };
    boundingBoxes.push_back(startright);

    BoundingBox treecol1 = { STARTING_BACKGROUND_X + 224, STARTING_BACKGROUND_Y + 160, TREE_WIDTH, 274 };
    boundingBoxes.push_back(treecol1);

    BoundingBox treecol2 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 240 };
    boundingBoxes.push_back(treecol2);

    BoundingBox treecol3 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    boundingBoxes.push_back(treecol3);
}