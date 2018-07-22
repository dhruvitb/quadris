#ifndef _LEVEL_4_H_
#define _LEVEL_4_H_
#include "level.h"

class Level4: public Level {
    std::ifstream file;
    bool random;
    int myLevel;
    int turnCount;
public:
    Level4();
    std::shared_ptr<GamePiece> generatePiece(std::string s) override;
    void resetTurnCount() override;
    // Level4:
    // When you generate a piece you need to do:
    //     1. Increase the turn count
    //     2. Check if turn count is equal to 5:
    //     3. If equal to 5:
    //         NotifyObservers (i.e. tell the grid to drop a bomb)
    //         Set the turnsSinceClear 0
    //     4. Generate a new piece
};

#endif