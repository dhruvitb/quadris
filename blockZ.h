#ifndef _BLOCK_Z_H_
#define _BLOCK_Z_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockZ: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{0,0},Coordinate{1,0},
    Coordinate{1,1},Coordinate{2,1}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif