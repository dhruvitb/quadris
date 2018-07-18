#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_
#include "level.h"

class Level4: public Level {
    int turnsSinceClear;
public:
    GamePiece generatePiece() override;
    bool generateBlock();
};

#endif