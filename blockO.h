#ifndef _BLOCK_O_H_
#define _BLOCK_O_H_
#include "gamepiece.h"
#include <vector>
#include "structures.h"

class BlockO: public GamePiece {
    std::vector<Coordinate> allCoords;
    Colour colour;
    char symbol;
    int levelGenerated;
public:
    BlockO(int levelGenerated);
    ~BlockO() override;
    
    void setCoords(std::vector<Coordinate> newCoords);

    std::vector<Coordinate> getCoords();

    Colour getColour();

    char getChar();
};

#endif