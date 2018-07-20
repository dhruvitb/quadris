#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_
#include "observer.h"
#include "subject.h"

class TextDisplay: public Observer<CellInfo> {
    std::vector<std::vector<char>> theDisplay;
public:
    TextDisplay();
    void print();
    bool notify(Subject<CellInfo> &from) override;
};

#endif