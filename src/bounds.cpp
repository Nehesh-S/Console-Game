#include "game.h"

void Game::addBoundingBoxes() {
    // topleft x, topleft y, width, height
    BoundingBox left_forest = { STARTING_BACKGROUND_X + 0, STARTING_BACKGROUND_Y + 0, TREE_WIDTH*3, MAP_HEIGHT };
    boundingBoxes.push_back(left_forest);

    BoundingBox right_forest = { STARTING_BACKGROUND_X + MAP_WIDTH - 3*TREE_WIDTH, STARTING_BACKGROUND_Y + 0, TREE_WIDTH*3, MAP_HEIGHT };
    boundingBoxes.push_back(right_forest);

    BoundingBox top_forest = { STARTING_BACKGROUND_X + TREE_WIDTH*3, STARTING_BACKGROUND_Y + 0, TREE_WIDTH*17, TREE_HEIGHT*2 };
    boundingBoxes.push_back(top_forest);

    BoundingBox bottom_forest = { STARTING_BACKGROUND_X + TREE_WIDTH*3, STARTING_BACKGROUND_Y + MAP_HEIGHT - 3*TREE_HEIGHT, TREE_WIDTH*17, TREE_HEIGHT*3 };
    boundingBoxes.push_back(bottom_forest);

    BoundingBox end = { STARTING_BACKGROUND_X + TREE_WIDTH*2, STARTING_BACKGROUND_Y + TREE_HEIGHT*2, TREE_WIDTH*4-32, TREE_HEIGHT*3-32 };
    boundingBoxes.push_back(end);

    BoundingBox startleft = { STARTING_BACKGROUND_X + TREE_WIDTH*3, STARTING_BACKGROUND_Y + MAP_HEIGHT - (3*TREE_HEIGHT + 32), TREE_WIDTH*8, 32 };
    boundingBoxes.push_back(startleft);

    BoundingBox startright = { STARTING_BACKGROUND_X + MAP_WIDTH - 9*TREE_WIDTH, STARTING_BACKGROUND_Y + MAP_HEIGHT - (3*TREE_HEIGHT + 32), TREE_WIDTH*6, 32 };
    boundingBoxes.push_back(startright);

    BoundingBox treecol1 = { STARTING_BACKGROUND_X + TREE_WIDTH*3 + GRASS_WIDTH*5, STARTING_BACKGROUND_Y + TREE_HEIGHT*5, TREE_WIDTH, TREE_HEIGHT*8 };
    boundingBoxes.push_back(treecol1);

    // BoundingBox treecol2 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 240 };
    // boundingBoxes.push_back(treecol2);

    // BoundingBox treecol3 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol3);
    
    // BoundingBox treecol4 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol4);
    
    // BoundingBox treecol5 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol5);
    
    // BoundingBox treecol6 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol6);
    
    // BoundingBox treecol7 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol7);
    
    // BoundingBox treecol8 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol8);
    
    // BoundingBox treecol9 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treecol9);
    
    // BoundingBox treerow1 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow1);
    
    // BoundingBox treerow2 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow2);
    
    // BoundingBox treerow3 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow3);
    
    // BoundingBox treerow4 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow4);
    
    // BoundingBox treerow5 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow5);
    
    // BoundingBox treerow6 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow6);
    
    // BoundingBox treerow7 = { STARTING_BACKGROUND_X + 352, STARTING_BACKGROUND_Y + 176, TREE_WIDTH, 304 };
    // boundingBoxes.push_back(treerow7);
}