#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_
#include <vector>
#include "structures.h"

class GamePiece {

protected:
    std::vector<Coordinate> allCoords;
    int levelGenerated;

public:
    virtual ~GamePiece() = 0;
    
    virtual std::vector<Coordinate> rotate(Rotation r) = 0;

    std::vector<Coordinate> shift(Direction d);

    void setCoords(std::vector<Coordinate>);

    std::vector<Coordinate> getCoords();

    virtual Colour getColour() = 0;

    virtual char getSymbol() = 0;

    //virtual void drop(); I don't think this is ever needed
};

#endif
