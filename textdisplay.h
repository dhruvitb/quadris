#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_
#include "observer.h"
#include "subject.h"
#include "structures.h"
#include <vector>

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
    const char I = 'I';
    const char J = 'J';
    const char L = 'L';
    const char O = 'O';
    const char S = 'S';
    const char Z = 'Z';
    const char T = 'T';
    const char BLANK = '-';
public:
    TextDisplay();
    void print();
    bool notify(Subject &from) override;
};

#endif