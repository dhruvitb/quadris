#include "blockJ.h"

BlockJ::BlockJ(int levelGenerated): colour{Colour::Blue}, symbol{'J'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,1});
    allCoords.emplace_back(Coordinate{2,1});
    allCoords.emplace_back(Coordinate{2,0});
}

BlockJ::~BlockJ() {
    
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