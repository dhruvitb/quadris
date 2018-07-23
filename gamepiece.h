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

    std::vector<Coordinate> shift(Direction d);

    virtual void setCoords(std::vector<Coordinate> newCoords);

    virtual std::vector<Coordinate> getCoords();

    virtual Colour getColour();

    virtual char getChar();

    //virtual void drop(); I don't think this is ever needed
};

#endif
