#include "blockhint.h"
#include <vector>

BlockHint::BlockHint() {
    isHeavy = false;
}

BlockHint::~BlockHint() {}

std::vector<Coordinate> BlockHint::rotate(Rotation r) {
    (void) r; // hint is incapable of rotation
    return std::vector<Coordinate>();
} 
    
Colour BlockHint::getColour() {
    return Colour::Black;
}

char BlockHint::getSymbol() {
    return '?';
}
