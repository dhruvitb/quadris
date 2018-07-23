#include "blockZ.h"

BlockZ::BlockZ(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{1,1}, Coordinate{1,2}};
}

BlockZ::~BlockZ() {
    
}

Colour BlockZ::getColour() {
    return Colour::Red;
}

char BlockZ::getSymbol() {
    return 'Z';
}