#include "cell.h"
using namespace std;

Cell::Cell(Coordinate position): position{position},
colour{Colour::NoColour} { 

}

CellInfo Cell::getInfo() const {
    char symbol = '-';
    if (piece) {
        symbol = piece->getSymbol();
    }
    return CellInfo{position.row, position.col, colour, symbol};
}

bool Cell::notify(Subject &from) {
    (void) from;
    return true; // this function might be unused yeah we should probably get rid of it ajknclsajnvisnc
}

void Cell::setColour(Colour c) {
    colour = c;
    notifyObservers(); // when a colour change occurs, notify its observers
}

void Cell::setPiece(shared_ptr<GamePiece> newPiece) {
    piece = newPiece;
}

shared_ptr<GamePiece> Cell::getPiece() {
    return piece;
}