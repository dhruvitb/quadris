#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include <memory>

class Cell: public Subject<CellInfo>, public Observer<CellInfo> {
    Coordinate position;
    Colour colour;
    std::shared_ptr<GamePiece> piece;
public:
    Cell(Coordinate c);
    CellInfo getInfo() const override;
    bool notify(Subject<CellInfo> &from) override;
};

#endif