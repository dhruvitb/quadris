#ifndef _CELL_H_
#define _CELL_H_
#include "structures.h"
#include "gamepiece.h"
#include "subject.h"
#include "observer.h"
#include "cell.h"
#include <memory>

class Cell: public Subject<CellInfo> {
    Coordinate position; // coordinates of the cell
    Colour colour; // colour of the cell
    std::shared_ptr<GamePiece> piece; // piece the cell has (once dropped)
public:
    // initialize with starting coordinate
    Cell(Coordinate c);
    // get the info of this cell defined in structures.h
    CellInfo getInfo() const override;
    // set the colour of this cell (also calls notifyObservers)
    void setColour(Colour c);
    // set the piece this cell has
    void setPiece(std::shared_ptr<GamePiece> newPiece);
    // get the piece this cell has
    shared_ptr<GamePiece> getPiece();
};

#endif
