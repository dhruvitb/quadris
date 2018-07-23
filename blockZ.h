#ifndef _BLOCK_Z_H_
#define _BLOCK_Z_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockZ: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockZ(int levelGenerated);
    ~BlockZ() override;
    void setCoords(std::vector<Coordinate> newCoords);

    std::vector<Coordinate> getCoords();

    Colour getColour();

    char getChar();
};

#endif