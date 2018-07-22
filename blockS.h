#ifndef _BLOCK_S_H_
#define _BLOCK_S_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockS: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockS(int levelGenerated);
    ~BlockS() override;
};

#endif