#ifndef _BLOCK_S_H_
#define _BLOCK_S_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockS: public GamePiece {

public:
    BlockS(int levelGenerated, bool isHeavy);
    ~BlockS() override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif
