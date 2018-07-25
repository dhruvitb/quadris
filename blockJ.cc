#include "blockJ.h"
using namespace std;

BlockJ::BlockJ(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{4,0},
    Coordinate{4,1}, Coordinate{4,2}};
    this->isHeavy = isHeavy;
}

BlockJ::~BlockJ() {
    
}

Colour BlockJ::getColour() {
    return Colour::Blue;
}

char BlockJ::getSymbol() {
    return 'J';
}