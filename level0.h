#ifndef _LEVEL_0_H_
#define _LEVEL_0_H_
#include "level.h"

class Level0: public Level {

public:
    GamePiece generatePiece() override;
};

#endif