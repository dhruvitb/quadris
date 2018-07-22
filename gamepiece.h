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

    std::vector<Coordinate> rotate(Rotation r);

    std::vector<Coordinate> shift(Direction d);

    void setCoords(std::vector<Coordinate>);

    std::vector<Coordinate> getCoords() const;

    //virtual void drop(); I don't think this is ever needed
};

#endif