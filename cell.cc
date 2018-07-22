#include "cell.h"
using namespace std;

Cell::Cell(Coordinate position): position{position},
colour{Colour::NoColour}, request{Request::NoRequest} {

}

CellInfo Cell::getInfo() const {
    return CellInfo{position.row, position.col, colour, request};
}

bool Cell::notify(Subject &from) {
    // figure out what needs to happen here THIS IS STILL BROKEN NEEDS TO BE FIXED
    CellInfo info = from.getInfo();
    Request r = info.request;
    if (r == Request::Clear) {
        if (colour != Colour::NoColour) {
            setRequest(Request::Clear);
            notifyObservers();
            return true;
        }
    } else if (r == Request::Drop) {
        setRequest(Request::Drop);
        notifyObservers();
        return true;
    }
    return false;
}

void Cell::setColour(Colour c) {
    colour = c;
}

void Cell::setPiece(shared_ptr<GamePiece> newPiece) {
    piece = newPiece;
}