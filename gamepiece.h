#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_
#include <vector>
#include "structures.h"

class GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:

    virtual ~GamePiece() = 0;

    std::vector<Coordinate> rotate(Rotation r);
        // make the thing rotate
        // check if it's within the bounds
        // also return a vector of its new positions

    std::vector<Coordinate> shift(Direction d);

    void setCoords(std::vector<Coordinate>);

    virtual void drop();
        // drop the piece
};

std::vector<Coordinate> GamePiece::shift(Direction d) {
    std::vector<Coordinate> copy = allCoords; // a vector we can mutate
    int size = copy.size();
    if (d == Direction::Right) {
        for (int i = 0; i < size; ++i) {
            ++copy[i].x;
        }
    } else if (d == Direction::Left) {
        for (int i = 0; i < size; ++i) {
            --copy[i].x;
        }
    } else {
        for (int i = 0; i < size; ++i) {
            ++copy[i].y;
        }
    }
    return copy;
}

std::vector<Coordinate> GamePiece::rotate(Rotation r) { 
    // TODO by Lisa
}

void GamePiece::setCoords(std::vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

#endif