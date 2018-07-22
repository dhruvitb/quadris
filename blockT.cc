#include "blockT.h"

BlockT::BlockT(int levelGenerated): colour{Colour::Purple}, symbol{'T'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,0});
    allCoords.emplace_back(Coordinate{1,1});
    allCoords.emplace_back(Coordinate{1,2});
}

BlockT::~BlockT() {
    
}