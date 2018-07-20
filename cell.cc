#include "cell.h"

Cell::Cell(Coordinate position, Colour colour): position{position},
colour{colour} {

}

Cell::~Cell() {
    
}

void Cell::setRequest(Request r) {
    request = r;
} 

CellInfo Cell::getInfo() {
    return CellInfo{position.x, position.y, colour, request};
}

bool Cell::notify(Subject &from) {
    // figure out what needs to happen here
    return true;
}

void Cell::attachObserver(Observer &ob) {
    observers.emplace_back(ob);
}