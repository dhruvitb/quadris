#ifndef _BLOCK_O_H_
#define _BLOCK_O_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockO: public GamePiece {
    Colour colour;
public:
    std::vector<Coordinate> rotate(Rotation r) override;
    std::vector<Coordinate> shift(Direction d) override;
    void drop() override;
};

#endif