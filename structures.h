#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <vector>
using namespace std;

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, NoColour, White};

enum class Direction {Left, Down, Right};

enum class Rotation {CW = 1, CCW = -1};

enum class Piece{I,J,L,O,S,Z,T};

enum class Request{Clear, Drop, NoRequest};

struct Coordinate {
    int row;
    int col;
    bool operator==(const Coordinate &other) {
        return (row == other.row && col == other.col);
    }
    bool operator!=(const Coordinate &other) {
        return !(*this == other);
    }
    Coordinate operator+(const Coordinate &other) {
        return Coordinate{row + other.row, col + other.col};
    }
    Coordinate operator-(const Coordinate &other) {
        return Coordinate{row - other.row, col - other.col};
    }
};

struct CellInfo {
    int row;
    int col;
    Colour colour;
    char symbol;
};

struct LevelInfo {
    bool dropBomb;
};

struct RotationCoordinatesL {
    const vector<vector<Coordinate>> RotationCoordinates{
        {Coordinate{0,0}, Coordinate{0,1}, Coordinate{0,2}, Coordinate{0,3}},
        {Coordinate{0,0}, Coordinate{1,0}, Coordinate{2,0}, Coordinate{3,0}}
    };
};

struct rotationCoordinates {
    vector<vector<Coordinate>> allRotations{
        {Coordinate{1,0}, Coordinate{1,1}, Coordinate{1,2}, Coordinate{2,0}, 
            Coordinate{2,1}, Coordinate{2,2}},
        {Coordinate{0,1}, Coordinate{1,1}, Coordinate{2,1}, Coordinate{0,0}, 
            Coordinate{1,0}, Coordinate{2,0}},
        {Coordinate{2,2}, Coordinate{2,1}, Coordinate{2,0}, Coordinate{1,2}, 
            Coordinate{1,1}, Coordinate{1,0}},
        {Coordinate{2,0}, Coordinate{1,0}, Coordinate{0,0}, Coordinate{2,1}, 
            Coordinate{1,1}, Coordinate{0,1}}
    };
    static Coordinate getLowerAndLeft() {
        return Coordinate{2,0}; //by our own definition
    }    
};
 
#endif