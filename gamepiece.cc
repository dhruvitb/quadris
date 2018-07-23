#include "gamepiece.h"
#include <iostream>
#include <vector>
using namespace std;

GamePiece::~GamePiece() {}

vector<Coordinate> GamePiece::shift(Direction d) {
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    int size = copy.size();
    if (d == Direction::Right) {
        for (auto& c: copy) {
            ++c.col;
        }
    } else if (d == Direction::Left) {
        for (auto& c: copy) {
            --c.col;
        }
    } else {
        for (auto& c: copy) {
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
