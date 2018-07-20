#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_
#include "level.h"

class Level4: public Level {
    int turnsSinceClear;
public:
    Level4();
    ~Level4();
    std::shared_ptr<GamePiece> generatePiece() override;
    PieceInfo getInfo();
    bool notifyObservers();
    bool generateBlock();
};

#endif