#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_
#include "level.h"

class Level4: public Level {

public:
    Level4();
    std::shared_ptr<GamePiece> generatePiece() override;
    int getMyLevel() override;
    void resetTurnCount() override;
    void incrementTurnCount() override;
};

#endif
