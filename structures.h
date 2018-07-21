#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <vector>

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, LightGrey, NoColour};

enum class Direction {Left, Down, Right};

enum class Rotation {CW, CCW};

enum class Piece{I,J,L,O,S,Z,T};

enum class Request{Clear, Drop, NoRequest};

struct Coordinate {
    int x;
    int y;
};

struct CellInfo {
    int x;
    int y;
    Colour colour;
    Request request;
};

struct LevelInfo {
    bool dropBomb;
};

#endif