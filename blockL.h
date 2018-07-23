#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockL: public GamePiece {

public:
    BlockL(int levelGenerated);
    ~BlockL() override;
    std::vector<Coordinate> rotate(Rotation r) override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif