#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_
#include "level.h"

class Level1: public Level {
    std::ifstream file;
    bool random;
    int myLevel;
public:
	Level1();
    std::shared_ptr<GamePiece> generatePiece() override;
};

#endif
