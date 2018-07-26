#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "structures.h"
#include "gamepiece.h"

class BlockBomb: public GamePiece {

public:
    BlockBomb();
    ~BlockBomb() override;
    std::vector<Coordinate> rotate(Rotation r) override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif
