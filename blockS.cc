#include "blockS.h"

BlockS::BlockS(int levelGenerated): colour{Colour::Green}, symbol{'S'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,2});
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,1});
    allCoords.emplace_back(Coordinate{1,0});
}

BlockS::~BlockS() {
    
}