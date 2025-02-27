#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_
#include <vector>
using namespace std;

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, NoColour, White}; // available colours

enum class Direction {Left, Down, Right}; // available movement directions

enum class Rotation {CW = 1, CCW = -1}; // available rotation directions

enum class Piece{I,J,L,O,S,Z,T}; // 

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
      
};

struct RotationCoordinatesI {
    // possible rotation configurations for the I block
    const vector<vector<Coordinate>> RotationCoordinates{
        {Coordinate{0,0}, Coordinate{0,1}, Coordinate{0,2}, Coordinate{0,3}},
        {Coordinate{0,0}, Coordinate{1,0}, Coordinate{2,0}, Coordinate{3,0}}
    };
};

struct rotationCoordinates {
    // possible rotation configurations for all 2x3 blocks
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
        return Coordinate{2,0}; //by our definition the default lowerleft
    }    
};
 
#endif
