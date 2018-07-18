#ifndef _BLOCK_L_H_
#define _BLOCK_L_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockL: public GamePiece {

public:
    std::vector<Coordinate> rotate(Rotation r) override;
    std::vector<Coordinate> shift(Direction d) override;
    void drop() override;
};

#endif