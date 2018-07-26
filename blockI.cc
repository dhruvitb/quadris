#include "blockI.h"
using namespace std;

BlockI::BlockI(int levelGenerated, bool isHeavy) {
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{3,2}, Coordinate{3,3}};
    rotationIndex = 0;
    this->isHeavy = isHeavy;
}

BlockI::~BlockI() {

}

Colour BlockI::getColour() {
    return Colour::Cyan;
}

char BlockI::getSymbol() {
    return 'I';
}

vector<Coordinate> BlockI::rotate(Rotation r) {
    (void) r; // only 2 positions; direction of rotation does not matter
    ++rotationIndex;
    vector<Coordinate> newCoords; 
    Coordinate lowerLeft = getLowerLeft();
    RotationCoordinatesI rotationCoords; // defined in structures.h
    for (Coordinate coord :
    rotationCoords.RotationCoordinates[rotationIndex % 2]) {
        // the direction of the rotation depends on the type of rotation that
        // needs to occur
        if (rotationIndex % 2 == 1) { 
            newCoords.emplace_back(lowerLeft - coord);
        } else {
            newCoords.emplace_back(lowerLeft + coord);
        }
    }
    return newCoords;
}

void BlockI::undoRotation(Rotation r) {
    (void) r; // if a rotation is invalid (off-screen/collision)
    --rotationIndex;
}
