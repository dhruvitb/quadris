#include "blockS.h"

BlockS::BlockS(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,1}, Coordinate{0,2},
    Coordinate{1,0}, Coordinate{1,1}};
}

BlockS::~BlockS() {
    
}

Colour BlockS::getColour() {
    return Colour::Green;
}

char BlockS::getSymbol() {
    return 'S';
}