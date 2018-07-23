#ifndef _BLOCK_I_H_
#define _BLOCK_I_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockI: public GamePiece {

public:
    BlockI(int levelGenerated);
    ~BlockI() override;
    std::vector<Coordinate> rotate(Rotation r) override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif