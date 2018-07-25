#include "gamepiece.h"
#include <iostream>
#include <vector>
#include "structures.h"
using namespace std;

GamePiece::~GamePiece() {}

int GamePiece::findRotationIndex(Rotation change) { //-1 if ccw, +1 if cw
    int c = static_cast<int>(change);
    if (rotationIndex + c >= 0 && rotationIndex + c <= 3) {
        return rotationIndex + c;
    } else if (rotationIndex + c > 3) {
        return (rotationIndex + c) % 4;
    } else { //curr + change < 0
        return (rotationIndex + c + 4);
    }
}

 vector<Coordinate> GamePiece::rotate(Rotation r) {
    rotationCoordinates c;
    vector<Coordinate> copy;
    Coordinate lowerLeft = getLowerLeft();
    vector<Coordinate> currentRotation = c.allRotations[rotationIndex];
    vector<Coordinate> nextRotation = c.allRotations[findRotationIndex(r)];
    Coordinate lowerLeftTemplate = rotationCoordinates::getLowerAndLeft();
    Coordinate offset = {lowerLeft.row - lowerLeftTemplate.row, 
                        lowerLeft.col - lowerLeftTemplate.col};
    int sizeCoords = allCoords.size();
    int sizeTemplate = currentRotation.size();
    for (int i = 0; i < sizeTemplate; ++i) {
        for (int j = 0; j < sizeCoords; ++j) {
            if (currentRotation[i] == templateCoord(allCoords[j], offset)) {
                copy.emplace_back(nextRotation[i] + offset);
            }
        }
    }
    rotationIndex = findRotationIndex(r);
    return copy;
}

vector<Coordinate> GamePiece::shift(Direction d) {
    vector<Coordinate> copy = allCoords; // a vector we can mutate
    if (d == Direction::Right) { // add to coordinates depending on direction
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

Coordinate GamePiece::templateCoord(Coordinate c, Coordinate offset) {
    return c - offset;
}

void GamePiece::setCoords(vector<Coordinate> newCoords) {
    allCoords = newCoords; 
}

std::vector<Coordinate> GamePiece::getCoords() {
    return allCoords; 
}

Coordinate GamePiece::getLowerLeft() {
    // return the lower left coordinate of the smallest bounding box
    Coordinate lowerLeft = allCoords[0];
    for (Coordinate coord : allCoords) {
        if (coord.row > lowerLeft.row) {
            lowerLeft.row = coord.row;
        } 
        if (coord.col < lowerLeft.col) {
            lowerLeft.col = coord.col;
        }
    }
    return lowerLeft;
}

void GamePiece::undoRotation(Rotation r) {
    int change = static_cast<int>(r);
    rotationIndex = rotationIndex - change;
    if (rotationIndex > 3) {
        rotationIndex = rotationIndex - 4;
    } else if (rotationIndex < 0) {
        rotationIndex = rotationIndex + 4;
    }
}

int GamePiece::getLevelGenerated() {
    return levelGenerated;
}

bool GamePiece::getIsHeavy() {
    return isHeavy;
}