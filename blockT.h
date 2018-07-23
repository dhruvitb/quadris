#ifndef _BLOCK_T_H_
#define _BLOCK_T_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockT: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockT(int levelGenerated);
    ~BlockT() override;
    void setCoords(std::vector<Coordinate> newCoords);

    std::vector<Coordinate> getCoords();

    Colour getColour();

    char getChar();
};

#endif