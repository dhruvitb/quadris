#include "cell.h"

Cell::Cell(Coordinate position): position{position},
colour{Colour::NoColour}, request{Request::NoRequest} {

}

CellInfo Cell::getInfo() const {
    return CellInfo{position.x, position.y, colour, request};
}

bool Cell::notify(Subject &from) {
    // figure out what needs to happen here

    return true;
}