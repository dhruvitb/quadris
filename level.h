#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include "gamepiece.h"
#include <memory>

class Level: public Subject {
    // remove the pieces field, replace with an enum class
    // find out how to add the input file streams
    bool random;
public:
    Level();
    ~Level();
    virtual std::shared_ptr<GamePiece> generatePiece() = 0;
    bool notifyObservers();
};

#endif