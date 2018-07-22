#include "blockL.h"

BlockL::BlockL(int levelGenerated): colour{Colour::Orange}, symbol{'L'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,0});
    allCoords.emplace_back(Coordinate{1,0});
    allCoords.emplace_back(Coordinate{2,0});
    allCoords.emplace_back(Coordinate{2,1});
}

BlockL::~BlockL() {
    
}