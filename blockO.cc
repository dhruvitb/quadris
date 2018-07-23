#include "blockO.h"
#include "iostream"

BlockO::BlockO(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{1,0}, Coordinate{1,1}};
}

BlockO::~BlockO() {
    
}

std::vector<Coordinate> BlockO::rotate(Rotation r) {
    return allCoords;
} 

Colour BlockO::getColour() {
    return Colour::Yellow;
}

char BlockO::getSymbol() {
    return 'O';
}