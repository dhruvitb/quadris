#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_
#include "level.h"

class Level2: public Level {
    std::ifstream file;
    bool random;
    int myLevel;
public:
	Level2();
    std::shared_ptr<GamePiece> generatePiece() override;
};

#endif
