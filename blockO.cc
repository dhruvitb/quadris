#include "blockO.h"

BlockO::BlockO(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1}, Coordinate{1,0}, Coordinate{1,1}};
}

BlockO::~BlockO() {
    
}

std::vector<Coordinate> BlockO::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 

Colour BlockO::getColour() {
    return Colour::Yellow;
}

char BlockO::getSymbol() {
    return 'O';
}