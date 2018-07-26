#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockL: public GamePiece {

public:
    BlockL(int levelGenerated, bool isHeavy);
    ~BlockL() override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif
