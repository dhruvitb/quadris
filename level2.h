#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_
#include "level.h"

class Level2: public Level {

public:
    Level2();
    ~Level2();
    std::shared_ptr<GamePiece> generatePiece() override;
    PieceInfo getInfo();
    bool notifyObservers();
};

#endif