#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <vector>
using namespace std;

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, LightGrey, NoColour};

enum class Direction {Left, Down, Right};

enum class Rotation {CW = 1, CCW = -1};

enum class Piece{I,J,L,O,S,Z,T};

enum class Request{Clear, Drop, NoRequest};

struct Coordinate {
    int row;
    int col;
};

struct CellInfo {
    int row;
    int col;
    Colour colour;
    Request request;
};

struct LevelInfo {
    bool dropBomb;
};

struct rotationCoordinates {
    vector<vector<Coordinate>> allRotations{
        {Coordinate{1,1}, Coordinate{1,2}, Coordinate{1,3}, Coordinate{2,1}, 
            Coordinate{2,2}, Coordinate{2,3}},
        {Coordinate{0,2}, Coordinate{1,2}, Coordinate{2,2}, Coordinate{0,1}, 
            Coordinate{1,1}, Coordinate{2,1}},
        {Coordinate{2,3}, Coordinate{2,2}, Coordinate{2,1}, Coordinate{1,3}, 
            Coordinate{1,2}, Coordinate{1,1}},
        {Coordinate{2,1}, Coordinate{1,1}, Coordinate{0,1}, Coordinate{2,2}, 
            Coordinate{1,2}, Coordinate{0,2}}
    };
    void getLowerLeft() {
        //fill this out plz
    }    
};
 
#endif