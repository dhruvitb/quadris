#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_
#include <vector>
#include "coordinate.h"

class GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    int levelGenerated;
public:
    std::vector<Coordinate> rotate(Rotation r);
        // make the thing rotate
        // check if it's within the bounds
        // also return a vector of its new positions

    std::vector<Coordinate> shift(Direction d);
        // same as above function

    void drop();
        // drop the piece
};

#endif