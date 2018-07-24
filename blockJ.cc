#include "blockJ.h"
#include <iostream>
using namespace std;

BlockJ::BlockJ(int levelGenerated) {
    //cout << "Generating block J" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{3,0}, Coordinate{3,1},
    Coordinate{3,2}, Coordinate{4,2}};
}

BlockJ::~BlockJ() {
    
}

Colour BlockJ::getColour() {
    return Colour::Blue;
}

char BlockJ::getSymbol() {
    return 'J';
}