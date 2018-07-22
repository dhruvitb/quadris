#include "gamepiece.h"
#include <vector>
using namespace std;

vector<Coordinate> GamePiece::shift(Direction d) {
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    int size = copy.size();
    if (d == Direction::Right) {
        for (int i = 0; i < size; ++i) {
            ++copy[i].x;
        }
    } else if (d == Direction::Left) {
        for (int i = 0; i < size; ++i) {
            --copy[i].x;
        }
    } else {
        for (int i = 0; i < size; ++i) {
            ++copy[i].y;
        }
    }
    return copy;
}

vector<Coordinate> GamePiece::rotate(Rotation r) { 
    // TODO by Lisa
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    return copy;
}

void GamePiece::setCoords(vector<Coordinate> newCoords) {
    allCoords = newCoords;
}

std::vector<Coordinate> GamePiece::getCoords() {
    return allCoords;
}

Colour GamePiece::getColour() {
    return colour;
}