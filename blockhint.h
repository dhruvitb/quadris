#ifndef _BLOCKHINT_H_
#define _BLOCKHINT_H_
#include <vector>
#include "gamepiece.h"

class BlockHint: public GamePiece {

public:
    BlockHint();
    ~BlockHint() override;
    std::vector<Coordinate> rotate(Rotation r) override;
    Colour getColour() override;
    char getSymbol() override;
};

#endif