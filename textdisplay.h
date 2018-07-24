#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_
#include "observer.h"
#include "subject.h"
#include "structures.h"
#include "gamepiece.h"
#include <vector>

class TextDisplay: public Observer<CellInfo> {
    std::vector<std::vector<char>> theDisplay;
    const char I = 'I';
    const char J = 'J';
    const char L = 'L';
    const char O = 'O';
    const char S = 'S';
    const char Z = 'Z';
    const char T = 'T';
    const char BLANK = '-';
    const char BOMB = '*';
public:
    TextDisplay();
    void print(int level, int score, int hiScore, shared_ptr<GamePiece> next);
    bool notify(Subject<CellInfo> &from) override;
};

#endif