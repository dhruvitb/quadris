#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include <memory>

class Cell: public Subject<CellInfo>, public Observer<CellInfo> {
    Coordinate position;
    Colour colour;
    Request request;
    std::shared_ptr<GamePiece> piece;
    std::vector<Observer<CellInfo>*> observers;
public:
    Cell(Coordinate c);
    CellInfo getInfo() const override;
    void setColour(Colour c);
    void setPiece(std::shared_ptr<GamePiece> newPiece);
    bool notify(Subject<CellInfo> &from) override;
};

#endif