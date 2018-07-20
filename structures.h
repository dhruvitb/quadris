#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, LightGrey, NoColour};

enum class Direction {Left, Down, Right};

enum class Rotation {CW, CCW};

enum class Piece{I,J,L,O,S,Z,T};

enum class Request{ClearLeft, ClearRight, };

struct Coordinate {
    int x;
    int y;
};

struct CellInfo {
    int x;
    int y;
    Colour c;
    Request r;
};

struct PieceInfo {
    vector<Coordinate> coords;
    Colour c;
    Direction d;
    Rotation r;
    Piece p;
};

#endif