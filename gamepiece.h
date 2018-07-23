#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_
#include <vector>
#include "structures.h"

class GamePiece {

protected:
    std::vector<Coordinate> allCoords;
    int levelGenerated;
    int rotationIndex;
    rotationCoordinates *c;

    int findRotationIndex(Rotation change);

public:
    virtual ~GamePiece() = 0;
    
    virtual std::vector<Coordinate> rotate(Rotation r);

    std::vector<Coordinate> shift(Direction d);

    Coordinate templateCoord(Coordinate c, Coordinate offset); //removes the offset amounts

    virtual void setCoords(std::vector<Coordinate> newCoords);

    virtual std::vector<Coordinate> getCoords();

    virtual Colour getColour() = 0;

    virtual char getSymbol() = 0;

    //virtual void drop(); I don't think this is ever needed
};

#endif
