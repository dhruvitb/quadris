#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "structures.h"
#include "gamepiece.h"

class BlockBomb: public GamePiece {
    std::vector<Coordinate> allCoords{Coordinate{0,5}};
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif