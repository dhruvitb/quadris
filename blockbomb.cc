#include "blockbomb.h"

BlockBomb::BlockBomb(): colour{Colour::Brown}, symbol{'*'} {
    
}

BlockBomb::~BlockBomb() {
    
}

void BlockBomb::setCoords(std::vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

std::vector<Coordinate> BlockBomb::getCoords() {
    return allCoords;
}

Colour BlockBomb::getColour() {
    return colour;
}

char BlockBomb::getChar() {
    return symbol;
}