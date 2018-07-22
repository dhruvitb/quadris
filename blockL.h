#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockL: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{0,0},Coordinate{0,1},
    Coordinate{0,2},Coordinate{1,2}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif