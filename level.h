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
protected:
    bool random = true; //whether it is randomly generated
    std::string fileName;
    std::ifstream fileInput;
    int turnCount; //for level 4 
public:
    std::shared_ptr<GamePiece> generatePieceFromString(std::string s);
    virtual std::shared_ptr<GamePiece> generatePiece() = 0;
    LevelInfo getInfo() const override;
    bool getIsRandom();
    void randomize(); //use when you want random input
    void changeFileName (std::string f); //random would be false
    void resetTurnCount(); // resets the turnsSinceClearedLine
    virtual int getMyLevel() = 0;
    void openFile(std::string newFile);
};

#endif
