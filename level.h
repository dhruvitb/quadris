#ifndef _LEVEL_H_
#define _LEVEL_H_
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "gamepiece.h"
#include "structures.h"
#include "subject.h"
#include <cstdlib>

class Level: public Subject<LevelInfo> {
protected:
    bool random = true; //whether it is randomly generated
    std::string fileName;
    std::ifstream fileInput;
    int turnCount = 0; //for level 4 
    std::string generateString();
    std::shared_ptr<GamePiece> generatePieceFromString(std::string s, bool 
    isHeavy);
    int randomInt(int num); 
    int seed;
public:
    Level();
    virtual std::shared_ptr<GamePiece> generatePiece() = 0;
    LevelInfo getInfo() const override;
    void randomize(); //use when you want random input
    void changeFileName (std::string f); 
    void changeSeed (int x);
    virtual void resetTurnCount(); // resets the turnsSinceClearedLine
    virtual int getMyLevel() = 0;
};

#endif
