#include "blockL.h"
#include <iostream>
using namespace std;

BlockL::BlockL(int levelGenerated) {
    cout << "Generating block L" << endl;
    this->levelGenerated = levelGenerated;
    allCoords = {Coordinate{0,0}, Coordinate{1,0}, Coordinate{2,0}, Coordinate{2,1}};
}

BlockL::~BlockL() {
    
}

std::vector<Coordinate> BlockL::rotate(Rotation r) {
    //stuff
    return std::vector<Coordinate>();
} 

Colour BlockL::getColour() {
    return Colour::Orange;
}

char BlockL::getSymbol() {
    return 'L';
}