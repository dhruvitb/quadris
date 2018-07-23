#include "blockI.h"

BlockI::BlockI(int levelGenerated): colour{Colour::Cyan}, symbol{'I'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,0});
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{0,2});
    allCoords.emplace_back(Coordinate{0,3});
}

BlockI::~BlockI() {
    
}

void BlockI::setCoords(std::vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

std::vector<Coordinate> BlockI::getCoords() {
    return allCoords;
}

Colour BlockI::getColour() {
    return colour;
}

char BlockI::getChar() {
    return symbol;
}