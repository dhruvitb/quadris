#include "blockT.h"

BlockT::BlockT(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{3,2}, Coordinate{4,1}};
    this->isHeavy = isHeavy;
}

BlockT::~BlockT() {
    
}

Colour BlockT::getColour() {
    return Colour::Purple;
}

char BlockT::getSymbol() {
    return 'T';
}