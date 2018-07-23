#include "blockI.h"
#include <iostream>
#include <vector>
using namespace std;

BlockI::BlockI(int levelGenerated) {
    cout << "Generating block I" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{0,2}, Coordinate{0,3}};
    rotationIndex = 0;
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
    (void) r;
    ++rotationIndex;
    vector<Coordinate> newCoords;
    Coordinate lowerLeft = getLowerLeft();
    RotationCoordinatesL rotationCoords;
    for (Coordinate coord :
    rotationCoords.RotationCoordinates[rotationIndex % 2]) {
        if (rotationIndex % 2 == 1) {
            newCoords.emplace_back(lowerLeft - coord);
        } else {
            newCoords.emplace_back(lowerLeft + coord);
        }
    }
    return newCoords;
}

void BlockI::undoRotation(Rotation r) {
    (void) r;
    --rotationIndex;
}