#include "blockO.h"
#include "iostream"

BlockO::BlockO(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{4,0}, Coordinate{4,1}};
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