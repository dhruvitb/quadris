#ifndef _TEXT_DISPLAY_H_
#define _TEXT_DISPLAY_H_
#include "vector"
#include "observer.h"

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
public:
    bool notify(Observer whoNotified) override;
    void print();
};

#endif 