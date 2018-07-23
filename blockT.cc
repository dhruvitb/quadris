#include "blockT.h"

BlockT::BlockT(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{0,2}, Coordinate{1,1}};
}

BlockT::~BlockT() {
    
}

Colour BlockT::getColour() {
    return Colour::Purple;
}

char BlockT::getSymbol() {
    return 'T';
}