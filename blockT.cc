#include "blockT.h"

BlockT::BlockT(int levelGenerated) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,1}, Coordinate{1,0}, Coordinate{1,1}, Coordinate{1,2}};
}

BlockT::~BlockT() {
    
}

std::vector<Coordinate> BlockT::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 

Colour BlockT::getColour() {
    return Colour::Purple;
}

char BlockT::getSymbol() {
    return 'T';
}