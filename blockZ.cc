#include "blockZ.h"

BlockZ::BlockZ(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{4,1}, Coordinate{4,2}};
}

BlockZ::~BlockZ() {
    
}

Colour BlockZ::getColour() {
    return Colour::Red;
}

char BlockZ::getSymbol() {
    return 'Z';
}