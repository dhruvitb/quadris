#ifndef _BLOCK_Z_H_
#define _BLOCK_Z_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockZ: public GamePiece {

public:
    BlockZ(int levelGenerated, bool isHeavy);
    ~BlockZ() override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif