#ifndef _BLOCK_Z_H_
#define _BLOCK_Z_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockZ: public GamePiece {

public:
    std::vector<Coordinate> rotate(Rotation r) override;
    std::vector<Coordinate> shift(Direction d) override;
    void drop() override;
};

#endif