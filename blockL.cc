#include "blockL.h"
#include <iostream>
using namespace std;

BlockL::BlockL(int levelGenerated) {
    //cout << "Generating block L" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{3,2}, Coordinate{4,0}};
}

BlockL::~BlockL() {
    
}

Colour BlockL::getColour() {
    return Colour::Orange;
}

char BlockL::getSymbol() {
    return 'L';
}