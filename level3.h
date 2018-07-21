#ifndef _LEVEL_3_H_
#define _LEVEL_3_H_
#include "level.h"

class Level3: public Level {

public:
    std::shared_ptr<GamePiece> generatePiece() override;
};

#endif