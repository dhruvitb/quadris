#ifndef _BLOCK_I_H_
#define _BLOCK_I_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockI: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockI(int levelGenerated);
    ~BlockI() override;
};

#endif