#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "gamepiece.h"
#include "structures.h"
#include "subject.h"

class Level: public Subject<LevelInfo> {
    std::ifstream file;
    bool random;
    int myLevel;
public:
    virtual std::shared_ptr<GamePiece> generatePiece() = 0;
    LevelInfo getInfo() const override;
    virtual void resetTurnCount(); // resets the turnsSinceClearedLine
};

#endif