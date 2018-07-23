#include "blockbomb.h"
#include <vector>

BlockBomb::BlockBomb() {}

BlockBomb::~BlockBomb() {}

std::vector<Coordinate> BlockBomb::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 
    
Colour BlockBomb::getColour() {
    return Colour::Brown;
}

char BlockBomb::getSymbol() {
    return '*';
}