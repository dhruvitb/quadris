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
    std::shared_ptr<GamePiece> generatePieceFromString(std::string s);
protected:
    bool random = true;
    std::string fileName;
    int turnCount;

public:
    virtual std::shared_ptr<GamePiece> generatePiece(std::string s) = 0;
    LevelInfo getInfo() const override;
    void resetTurnCount(); // resets the turnsSinceClearedLine
    virtual int getMyLevel() = 0;
};

#endif
