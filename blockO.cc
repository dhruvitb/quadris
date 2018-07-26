#include "blockO.h"

BlockO::BlockO(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{4,0}, Coordinate{4,1}};
    this->isHeavy = isHeavy;
}

BlockO::~BlockO() {
    
}

std::vector<Coordinate> BlockO::rotate(Rotation r) {
    (void) r;
    return allCoords;
} 

Colour BlockO::getColour() {
    return Colour::Yellow;
}

char BlockO::getSymbol() {
    return 'O';
}
