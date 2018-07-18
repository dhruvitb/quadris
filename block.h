#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class Block: public GamePiece {

public:
    std::vector<Coordinate> rotate(Rotation r) override;
    std::vector<Coordinate> shift(Direction d) override;
    void drop() override;
};

#endif