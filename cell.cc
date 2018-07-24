#include "cell.h"
using namespace std;

Cell::Cell(Coordinate position): position{position},
colour{Colour::NoColour}, request{Request::NoRequest} {

}

CellInfo Cell::getInfo() const {
    char symbol = '-';
    if (piece != nullptr) {
        symbol = piece->getSymbol();
    }
    return CellInfo{position.row, position.col, colour, symbol};
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