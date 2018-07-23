#include "blockJ.h"
#include <iostream>
using namespace std;

BlockJ::BlockJ(int levelGenerated) {
    cout << "Generating block J" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{0,1},
    Coordinate{0,2}, Coordinate{1,2}};
}

BlockJ::~BlockJ() {
    
}

Colour BlockJ::getColour() {
    return Colour::Blue;
}

char BlockJ::getSymbol() {
    return 'J';
}