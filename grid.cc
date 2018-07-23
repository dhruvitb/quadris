#include "grid.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "blockbomb.h"
#include "blockO.h"
#include "gamepiece.h"
#include <set>
using namespace std;

int Grid::highScore = 0;

Grid::Grid(): turnCount{0}, currentLevel{0}, score{0}, td{}/*, gd{}*/ {
    levelFactory = make_shared<Level0>();
    levelFactory->attach(this);
    currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}};
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // attach the up and right cell as observer
            theGrid[i][j].attach(&td);
            if (inBounds(i - 1, j, height, width)) {
                //theGrid[i][j].attach(&(theGrid[i-1][j]));
            }
            if (inBounds(i, j + 1, height, width)) {
                //theGrid[i][j].attach(&(theGrid[i][j+1]));
            }
        }
    }
    vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (Coordinate coord : initialCoords) {
        theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
        theGrid[coord.row][coord.col].notifyObservers();
    }
    print();
}

Grid::~Grid() {

}

bool Grid::inBounds(int i, int j, int maxI, int maxJ) {
    // helper function to find out if a coordinate is in the grid
    return (i < maxI && i >= 0 && j < maxJ && j >= 0);
}

void Grid::print() {
    td.print(currentLevel, score, highScore);
}

void Grid::drop() {
    while (shiftPiece(Direction::Down));
    // vector<Coordinate> finalCoords = currentPiece->getCoords();
    // set<int> rowsSpanned;
    // for (Coordinate coord : finalCoords) {
    //     rowsSpanned.insert(coord.row);
    // }
    getNextPiece();
    //gameOver();
}

bool Grid::movePiece(vector<Coordinate> newCoords) {
    bool valid = true;
    vector<Coordinate> oldCoords = currentPiece->getCoords();
    for (Coordinate coord : oldCoords) {
            theGrid[coord.row][coord.col].setColour(Colour::NoColour);
            theGrid[coord.row][coord.col].notifyObservers();
    }
    for (Coordinate coord : newCoords) {
        if (!inBounds(coord.row, coord.col, height, width) ||
        theGrid[coord.row][coord.col].getInfo().colour != Colour::NoColour) {
            valid = false;
            break;
        }
    }
    if (valid) {
        currentPiece->setCoords(newCoords);
    } else {
        for (Coordinate coord : oldCoords) {
            theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
            theGrid[coord.row][coord.col].notifyObservers();
        }
    }
    return valid;
}

bool Grid::shiftPiece(Direction d) {
    vector<Coordinate> newPosition = currentPiece->shift(d);
    if (movePiece(newPosition)) {
        for (Coordinate coord : newPosition) {
            theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
            theGrid[coord.row][coord.col].notifyObservers();
        }
        return true;
    }
    return false;
}

bool Grid::rotatePiece(Rotation r) {
    vector<Coordinate> newPosition = currentPiece->rotate(r);
    if (movePiece(newPosition)) {
        for (Coordinate coord : newPosition) {
            theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
            theGrid[coord.row][coord.col].notifyObservers();
        }
        return true;
    }
    currentPiece->undoRotation(r);
    return false;
}

void Grid::getNextPiece() {
    currentPiece = nextPiece;
    nextPiece = levelFactory->generatePiece(); //consider file or random
    vector<Coordinate> newPieceCoords = currentPiece->getCoords();
    for (Coordinate coord : newPieceCoords) {
        theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
        theGrid[coord.row][coord.col].notifyObservers();
    }
}

void Grid::incrementLevel() {
    if (currentLevel == 0) {
        levelFactory = make_shared<Level1>();
    } else if (currentLevel == 1) {
        levelFactory = make_shared<Level2>();
    } else if (currentLevel == 2) {
        levelFactory = make_shared<Level3>();
    } else { // changeLevel checks if the level is in bounds
        levelFactory = make_shared<Level4>();
    }
}

void Grid::decrementLevel() {
    if (currentLevel == 4) {
        levelFactory = make_shared<Level3>();
    } else if (currentLevel == 3) {
        levelFactory = make_shared<Level2>();
    } else if (currentLevel == 2) {
        levelFactory = make_shared<Level1>();
    } else { // changeLevel checks if the level is in bounds
        levelFactory = make_shared<Level0>();
    }
}

void Grid::levelUp() {
    if (currentLevel < LEVEL_MAX) {
        ++currentLevel;
        incrementLevel();
    }
}

void Grid::levelDown() {
    if (currentLevel > LEVEL_MIN) {
        --currentLevel;
        decrementLevel();
    }
}

void Grid::updateFileName(string s) {
    if (currentLevel == 3 || currentLevel == 4) {
        levelFactory->changeFileName(s);
    }
}

void Grid::restoreRandom() {
    if (currentLevel != 0) {
        levelFactory->randomize();
    }
}

void Grid::gameOver() {
    // find out how to implement this
    // it will probably call restart
    vector<Coordinate> coords = currentPiece->getCoords();
    for (Coordinate coord : coords) {
        if (coord.row > 15) { // this is the wrong way around
            cout << "YOU LOSE" << endl; // find out what exactly to do when the game is over
        }
    }
}

void Grid::restart() {
    if (score > this->highScore) {
        highScore = score;
    }
    //enter fields of grid that need to be changed when restarted
}

void Grid::hint() {
    // find out how to implement this
}

int Grid::getScore() {
    return score;
}

bool Grid::notify(Subject<LevelInfo> &from) {
    // switch the current piece to a bomb, drop it, switch back
    shared_ptr<GamePiece> temp = currentPiece;
    currentPiece = make_shared<BlockBomb>();
    drop();
    currentPiece = temp;
    return true;
}