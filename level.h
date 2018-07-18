#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include "gamepiece.h"

class Level: public Subject {
    // remove the pieces field, replace with an enum class
    // find out how to add the input file streams
    bool random;
public:
    virtual GamePiece generatePiece() = 0;
};

#endif