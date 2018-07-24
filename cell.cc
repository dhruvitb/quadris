#include "cell.h"
using namespace std;

Cell::Cell(Coordinate position): position{position},
colour{Colour::NoColour}, request{Request::NoRequest} {

}

CellInfo Cell::getInfo() const {
    return CellInfo{position.row, position.col, colour, request};
}

bool Cell::notify(Subject &from) {
    (void) from;
    return true; // this function might be unused
}

void Cell::setColour(Colour c) {
    colour = c;
    notifyObservers();
}

void Cell::setPiece(shared_ptr<GamePiece> newPiece) {
    piece = newPiece;
}

shared_ptr<GamePiece> Cell::getPiece() {
    return piece;
}