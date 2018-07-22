#ifndef _BLOCK_I_H_
#define _BLOCK_I_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockI: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{0,0},Coordinate{1,0},
    Coordinate{2,0},Coordinate{3,0}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif