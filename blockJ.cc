#include "blockJ.h"
#include <iostream>
using namespace std;

BlockJ::BlockJ(int levelGenerated) {
    cout << "Generating block J" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,1}, Coordinate{1,1},
    Coordinate{2,1}, Coordinate{2,0}};
}

BlockJ::~BlockJ() {
    
}

std::vector<Coordinate> BlockJ::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 

Colour BlockJ::getColour() {
    return Colour::Blue;
}

char BlockJ::getSymbol() {
    return 'J';
}