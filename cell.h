#ifndef _CELL_H_
#define _CELL_H_
#include "coordinate.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"

class Cell: public Subject, public Observer {
    Coordinate position;
    Colour colour;
    GamePiece piece;
public:

};

#endif