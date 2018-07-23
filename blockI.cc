#include "blockI.h"
#include <iostream>
#include <vector>
using namespace std;

BlockI::BlockI(int levelGenerated) {
    cout << "Generating block I" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1}, Coordinate{0,2}, Coordinate{0,3}};
}

BlockI::~BlockI() {
    
}

std::vector<Coordinate> BlockI::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 

Colour BlockI::getColour() {
    return Colour::Cyan;
}

char BlockI::getSymbol() {
    return 'I';
}