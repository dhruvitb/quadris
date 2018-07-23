#include "blockL.h"
#include <iostream>
using namespace std;

BlockL::BlockL(int levelGenerated) {
    cout << "Generating block L" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{0,2}, Coordinate{1,0}};
}

BlockL::~BlockL() {
    
}

Colour BlockL::getColour() {
    return Colour::Orange;
}

char BlockL::getSymbol() {
    return 'L';
}