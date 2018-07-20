#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include <memory>

class Cell: public Subject, public Observer {
    Coordinate position;
    Colour colour;
    std::shared_ptr<GamePiece> piece;
public:
    Cell(Coordinate position, Colour colour);
    CellInfo getInfo();
};

#endif