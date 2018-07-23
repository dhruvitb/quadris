#ifndef _BLOCK_J_H_
#define _BLOCK_J_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockJ: public GamePiece {

public:
    BlockJ(int levelGenerated);
    ~BlockJ() override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif