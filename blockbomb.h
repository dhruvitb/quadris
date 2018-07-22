#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "structures.h"
#include "gamepiece.h"

class BlockBomb: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
};

#endif