#include "blockO.h"
#include "iostream"

BlockO::BlockO(int levelGenerated): colour{Colour::Yellow}, symbol{'O'},
levelGenerated{levelGenerated} {
    std::cout << "the block says it's character is: " << symbol << std::endl;
    allCoords.emplace_back(Coordinate{0,0});
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,0});
    allCoords.emplace_back(Coordinate{1,1});
    std::cout << "The block says it's size is: " << allCoords.size() << std::endl;
}

BlockO::~BlockO() {
    
}

void BlockO::setCoords(std::vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

std::vector<Coordinate> BlockO::getCoords() {
    return allCoords;
}

Colour BlockO::getColour() {
    return colour;
}

char BlockO::getChar() {
    return symbol;
}