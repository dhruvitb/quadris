#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_
#include "level.h"

class Level2: public Level {

public:
    GamePiece generatePiece() override;
};

#endif