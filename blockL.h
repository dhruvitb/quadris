#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockL: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockL(int levelGenerated);
    ~BlockL() override;
};

#endif