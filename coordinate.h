#ifndef _COORDINATE_H_
#define _COORDINATE_H_

enum class Colour {Cyan, Blue, Orange, Yellow, Green, Red, Purple, Brown,
                    Black, LightGrey, NoColour};

enum class Direction {Left, Down, Right};

enum class Rotation {CW, CCW};

struct Coordinate {
    int x;
    int y;
};

#endif