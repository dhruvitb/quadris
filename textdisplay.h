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
    const char HINT = '?';
    // reduces similar code to print gamePieces for next/held
    void printPiece(shared_ptr<GamePiece> piece);
public:
    TextDisplay();
    // print the text display and associated info
    void print(int level, int score, int hiScore, shared_ptr<GamePiece> next,
    shared_ptr<GamePiece> held);
    bool notify(Subject<CellInfo> &from) override;
};

#endif
