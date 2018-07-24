#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include <memory>

class Cell: public Subject<CellInfo>, public Observer<CellInfo> {
    Coordinate position; // coordinates of the cell
    Colour colour; // colour of the cell
    Request request; // unused we should probably get rid of this in general kjnvlasjnljsnvkadjfnvj
    std::shared_ptr<GamePiece> piece; // piece the cell has (once dropped)
    std::vector<Observer<CellInfo>*> observers; // observers of the cell
public:
    // initialize with starting coordinate
    Cell(Coordinate c);
    // get the info of this cell defined in structures.h
    CellInfo getInfo() const override;
    // set the colour of this cell
    void setColour(Colour c);
    // set the piece this cell has
    void setPiece(std::shared_ptr<GamePiece> newPiece);
    // get the piece this cell has
    shared_ptr<GamePiece> getPiece();
    // this might not be needed anymore since the cells do not observer each other oankajnclsjnckjnc
    bool notify(Subject<CellInfo> &from) override;
};

#endif