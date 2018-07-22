#ifndef _BLOCK_S_H_
#define _BLOCK_S_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockS: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{2,0}, Coordinate{1,0},
    Coordinate{1,1},Coordinate{0,1}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif