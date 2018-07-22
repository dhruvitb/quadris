#ifndef _BLOCK_O_H_
#define _BLOCK_O_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockO: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{0,0},Coordinate{0,1},
    Coordinate{1,0},Coordinate{0,1}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif