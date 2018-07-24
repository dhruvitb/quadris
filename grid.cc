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
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"
#include "blockbomb.h"
#include "gamepiece.h"
#include <set>
#include <algorithm>
#include <cmath>
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
                theGrid[i][j].attach(&(theGrid[i-1][j]));
            }
            if (inBounds(i, j + 1, height, width)) {
                theGrid[i][j].attach(&(theGrid[i][j+1]));
            }
        }
    }
    vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (Coordinate coord : initialCoords) {
        theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
        //theGrid[coord.row][coord.col].notifyObservers();
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

bool Grid::checkClear(int row) {
    for (int i = 0; i < width; ++i) {
        if (theGrid[row][i].getInfo().colour == Colour::NoColour) {
            return false;
        }
    }
    return true;
}

void Grid::dropRows(int row) {
    while (row > 0) {
        for (int i = 0; i < width; ++i) {
            theGrid[row-1][i].setColour(Colour::NoColour);
            shared_ptr<GamePiece> cellsPiece = theGrid[row-1][i].getPiece();
            if (cellsPiece) {
                vector<Coordinate> temp = cellsPiece->getCoords();
                for (Coordinate &c : temp) {
                    if (c.row == row - 1) {
                        c.row = row;
                        theGrid[row-1][c.col].setPiece(nullptr);
                        theGrid[row][c.col].setPiece(cellsPiece);
                    }
                    theGrid[c.row][c.col].setColour(cellsPiece->getColour());
                }
                cellsPiece->setCoords(temp);
            }
        }
        --row;
    }
}

void Grid::clearRows() {
    vector<Coordinate> finalCoords = currentPiece->getCoords();
    set<int> rowsSpanned;
    int rowsCleared = 0;
    for (Coordinate coord : finalCoords) {
        rowsSpanned.insert(coord.row);
    }
    for (int row : rowsSpanned) {
        if (checkClear(row)) {
            ++rowsCleared;
            for (int i = 0; i < width; ++i) {
                vector<Coordinate> temp =
                theGrid[row][i].getPiece()->getCoords();
                temp.erase(std::remove(temp.begin(), temp.end(), 
                Coordinate{row,i}), temp.end());
                theGrid[row][i].getPiece()->setCoords(temp);
                theGrid[row][i].setColour(Colour::NoColour);
                if (temp.size() == 0) {
                    score += pow(
                    (theGrid[row][i].getPiece()->getLevelGenerated() + 1), 2);
                }
                //theGrid[row][i].notifyObservers();
            }
            dropRows(row);
        }
    }
    score += pow((rowsCleared + currentLevel), 2);
    if (score > highScore) {
        highScore = score;
    }
}

void Grid::drop() {
    while (shiftPiece(Direction::Down));
    vector<Coordinate> finalCoords = currentPiece->getCoords();
    for (Coordinate coord : finalCoords) {
        theGrid[coord.row][coord.col].setPiece(currentPiece);
    }
    clearRows();
    getNextPiece();
    //gameOver();
}

bool Grid::movePiece(vector<Coordinate> newCoords) {
    bool valid = true;
    vector<Coordinate> oldCoords = currentPiece->getCoords();
    for (Coordinate coord : oldCoords) {
            theGrid[coord.row][coord.col].setColour(Colour::NoColour);
            //theGrid[coord.row][coord.col].notifyObservers();
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
            //theGrid[coord.row][coord.col].notifyObservers();
        }
    }
    return valid;
}

bool Grid::shiftPiece(Direction d) {
    vector<Coordinate> newPosition = currentPiece->shift(d);
    if (movePiece(newPosition)) {
        for (Coordinate coord : newPosition) {
            theGrid[coord.row][coord.col].setColour(currentPiece->getColour());
            //theGrid[coord.row][coord.col].notifyObservers();
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
            //theGrid[coord.row][coord.col].notifyObservers();
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
        //theGrid[coord.row][coord.col].notifyObservers();
    }
}

void Grid::updateLevelFactory() {
    if (currentLevel == 4) {
        levelFactory = make_shared<Level4>();
    } else if (currentLevel == 3) {
        levelFactory = make_shared<Level3>();
    } else if (currentLevel == 2) {
        levelFactory = make_shared<Level2>();
    } else if (currentLevel == 1) {
        levelFactory = make_shared<Level1>();
    } else { // changeLevel checks if the level is in bounds
        levelFactory = make_shared<Level0>();
    }
}

void Grid::levelUp() {
    if (currentLevel < LEVEL_MAX) {
        ++currentLevel;
        updateLevelFactory();
        cout << "current level is: " << currentLevel << endl;
    }
}

void Grid::levelDown() {
    if (currentLevel > LEVEL_MIN) {
        --currentLevel;
        updateLevelFactory();
    }
    cout << "current level is: " << currentLevel << endl;
}

void Grid::updateFileName(string s) {
    if (currentLevel == 0 || currentLevel == 3 || currentLevel == 4) {
        levelFactory->changeFileName(s);
    }
}

void Grid::restoreRandom() {
    if (currentLevel == 3 || currentLevel == 4) {
        levelFactory->randomize();
    }
}

void Grid::replaceCurrentPiece(string s) {
    vector<Coordinate> oldCoords = currentPiece->getCoords();
    for (Coordinate c : oldCoords) {
        theGrid[c.row][c.col].setColour(Colour::NoColour);
    }
    if (s == "I") {
		currentPiece = make_shared<BlockI>(currentLevel);
	} else if (s == "J") {
		currentPiece = make_shared<BlockJ>(currentLevel);
	} else if (s == "L") {
		currentPiece = make_shared<BlockL>(currentLevel);
	} else if (s == "O") {
		currentPiece = make_shared<BlockO>(currentLevel);
	} else if (s == "S") {
		currentPiece = make_shared<BlockS>(currentLevel);
	} else if (s == "Z") {
		currentPiece = make_shared<BlockZ>(currentLevel);
	} else { //s == "T"
		currentPiece = make_shared<BlockT>(currentLevel);
	}    
    vector<Coordinate> temp = currentPiece->getCoords();
    for (Coordinate c : temp) {
        theGrid[c.row][c.col].setColour(currentPiece->getColour());
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
    (void) from;
    shared_ptr<GamePiece> temp = currentPiece;
    currentPiece = make_shared<BlockBomb>();
    drop();
    currentPiece = temp;
    return true;
}