#include "blockZ.h"

BlockZ::BlockZ(int levelGenerated): colour{Colour::Red}, symbol{'Z'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,0});
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,1});
    allCoords.emplace_back(Coordinate{1,2});
}

BlockZ::~BlockZ() {
    
}