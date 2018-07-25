#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_
#include <vector>
#include "structures.h"

class GamePiece {

protected:
    std::vector<Coordinate> allCoords;
    int levelGenerated; // level block was generated in
    int rotationIndex = 0; // rotation configuration found in structures.h
    int squaresDeleted = 0;  // counter for if entire piece is cleared
    bool isHeavy = false; // is the piece heavy? (level 3 and 4)
    int findRotationIndex(Rotation change); // for 2x3 bounding box pieces
    // applies offset amount to rotation
    Coordinate templateCoord(Coordinate c, Coordinate offset); 
public:
    virtual ~GamePiece() = 0;
    // rotates the gamePiece in the given direction of rotation, r
    virtual std::vector<Coordinate> rotate(Rotation r);
    // moves the piece in direction, d
    std::vector<Coordinate> shift(Direction d);
    // returns lower left of bounding box
    virtual Coordinate getLowerLeft();
    // sets the coordinates of a gamepiece to be the given coordinates
    virtual void setCoords(std::vector<Coordinate> newCoords);
    // get the coordinates of this gamepiece
    virtual std::vector<Coordinate> getCoords();
    // get the colour of this gamepiece
    virtual Colour getColour() = 0;
    // get the symbol of this gamepiece
    virtual char getSymbol() = 0;
    // if the roation is invalid, it resets the rotation index back
    virtual void undoRotation(Rotation r);
    // get the level that this piece was generated on
    virtual int getLevelGenerated();
    // find out of the piece is heavy or not (level 3 and 4)
    virtual bool getIsHeavy();
    virtual void setRotationIndex(int i);
    virtual int getRotationIndex();
};

#endif
