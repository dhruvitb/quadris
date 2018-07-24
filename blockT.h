#ifndef _BLOCK_T_H_
#define _BLOCK_T_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockT: public GamePiece {

public:
    BlockT(int levelGenerated, bool isHeavy);
    ~BlockT() override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif