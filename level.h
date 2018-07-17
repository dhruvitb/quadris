#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include "gamepiece.h"

class Level {
    std::vector<GamePiece> pieces;
    // find out how to add the input file streams
    bool random;
public:
    GamePiece generatePiece();
};

#endif