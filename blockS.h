#ifndef _BLOCK_S_H_
#define _BLOCK_S_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockS: public GamePiece {

public:
    std::vector<Coordinate> rotate(Rotation r) override;
    std::vector<Coordinate> shift(Direction d) override;
    void drop() override;
};

#endif