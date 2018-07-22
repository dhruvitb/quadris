#ifndef _BLOCK_J_H_
#define _BLOCK_J_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockJ: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{1,0},Coordinate{1,1},
    Coordinate{1,2},Coordinate{0,2}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif