#include "blockbomb.h"
#include <vector>

BlockBomb::BlockBomb() {
    allCoords = {Coordinate{3,5}};
}

BlockBomb::~BlockBomb() {}

std::vector<Coordinate> BlockBomb::rotate(Rotation r) {
    (void) r; // bomb is incapable of rotation
    return std::vector<Coordinate>();
} 
    
Colour BlockBomb::getColour() {
    return Colour::Brown;
}

char BlockBomb::getSymbol() {
    return '*';
}
