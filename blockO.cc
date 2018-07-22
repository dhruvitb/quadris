#include "blockO.h"

BlockO::BlockO(int levelGenerated): colour{Colour::Yellow}, symbol{'O'},
levelGenerated{levelGenerated} {
    allCoords.emplace_back(Coordinate{0,0});
    allCoords.emplace_back(Coordinate{0,1});
    allCoords.emplace_back(Coordinate{1,0});
    allCoords.emplace_back(Coordinate{1,1});
}