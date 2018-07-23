#include "gamepiece.h"
#include <vector>
using namespace std;

GamePiece::~GamePiece() {}

vector<Coordinate> GamePiece::shift(Direction d) {
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    int size = copy.size();
    if (d == Direction::Right) {
        for (int i = 0; i < size; ++i) {
            ++copy[i].col;
        }
    } else if (d == Direction::Left) {
        for (int i = 0; i < size; ++i) {
            --copy[i].col;
        }
    } else {
        for (int i = 0; i < size; ++i) {
            ++copy[i].row;
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
