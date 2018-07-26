#ifndef _LEVEL_3_H_
#define _LEVEL_3_H_
#include "level.h"

class Level3: public Level {

public:
    Level3();
    std::shared_ptr<GamePiece> generatePiece() override;
    int getMyLevel() override;
};

#endif
