#include "gamepiece.h"
#include <iostream>
#include <vector>
using namespace std;

GamePiece::~GamePiece() {}

vector<Coordinate> GamePiece::shift(Direction d) {
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    if (d == Direction::Right) {
        for (Coordinate &c: copy) {
            ++c.col;
        }
    } else if (d == Direction::Left) {
        for (Coordinate &c: copy) {
            --c.col;
        }
    } else {
        for (Coordinate &c: copy) {
            ++c.row;
        }
    }
    return copy;
}

void GamePiece::setCoords(vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

std::vector<Coordinate> GamePiece::getCoords() {
    return allCoords;
}

Coordinate GamePiece::getLowerLeft() {
    Coordinate lowerLeft = allCoords[0];
    for (Coordinate coord : allCoords) {
        if (coord.row > lowerLeft.row && coord.col < lowerLeft.col) {
            lowerLeft = coord;
        }
    }
    return lowerLeft;
}

void GamePiece::undoRotation(Rotation r) {
    rotationIndex += (-1 * static_cast<int>(r));
}