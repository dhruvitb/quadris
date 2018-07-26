#ifndef _BLOCK_O_H_
#define _BLOCK_O_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockO: public GamePiece {

public:
    BlockO(int levelGenerated, bool isHeavy);
    ~BlockO() override;
    std::vector<Coordinate> rotate(Rotation r) override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif
