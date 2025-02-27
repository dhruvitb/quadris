#include "blockS.h"

BlockS::BlockS(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,1}, Coordinate{3,2},
    Coordinate{4,0}, Coordinate{4,1}};
    this->isHeavy = isHeavy;
}

BlockS::~BlockS() {
    
}

Colour BlockS::getColour() {
    return Colour::Green;
}

char BlockS::getSymbol() {
    return 'S';
}
