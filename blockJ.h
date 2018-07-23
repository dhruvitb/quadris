#ifndef _BLOCK_J_H_
#define _BLOCK_J_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockJ: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockJ(int levelGenerated);
    ~BlockJ() override;
    void setCoords(std::vector<Coordinate> newCoords);

    std::vector<Coordinate> getCoords();

    Colour getColour();

    char getChar();
};

#endif