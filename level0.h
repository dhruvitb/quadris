#ifndef _LEVEL_0_H_
#define _LEVEL_0_H_
#include "level.h"

class Level0: public Level {

public:
    Level0();
    ~Level0();
    std::shared_ptr<GamePiece> generatePiece() override;
    PieceInfo getInfo();
    bool notifyObservers();
};

#endif