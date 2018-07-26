#include "blockL.h"
using namespace std;

BlockL::BlockL(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,2}, Coordinate{4,0},
    Coordinate{4,1}, Coordinate{4,2}};
    this->isHeavy = isHeavy;
}

BlockL::~BlockL() {
    
}

Colour BlockL::getColour() {
    return Colour::Orange;
}

char BlockL::getSymbol() {
    return 'L';
}
