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
#include "window.h"
#include "graphicsdisplay.h"
#include "X11/Xlib.h"
using namespace std;

int Grid::highScore = 0;

Grid::Grid(): turnCount{0}, currentLevel{0}, score{0}, td{}, gd{385, 630} {
    //Dhruvit to to get the window not to appear upon executing constructor
    updateLevelFactory();
    //levelFactory->attach(this);
    /*currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();*/
    /*for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}};
            c.attach(&td);
            //c.attach(&gd);
            c.notifyObservers(); //is this still necessary?
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }*/
    // for (int i = 0; i < height; ++i) {
    //     for (int j = 0; j < width; ++j) {
    //         // attach the up and right cell as observer
    //         theGrid[i][j].attach(&td);
    //         if (inBounds(i - 1, j, height, width)) {
    //             theGrid[i][j].attach(&(theGrid[i-1][j])); // CELLS NO LONGER OBSERVE EACH OTHER LOL
    //         }
    //         if (inBounds(i, j + 1, height, width)) {
    //             theGrid[i][j].attach(&(theGrid[i][j+1])); // CELLS NO LONGER OBSERVE EACH OTHER LOL
    //         }
    //     }
    // }

    /*vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (Coordinate c : initialCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            theGrid[c.row][c.col].setColour(currentPiece->getColour());
        }
    }*/
    //print();
}

Grid::~Grid() {}

void Grid::init() {
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}};
            if (!graphicsOnly) {
                c.attach(&td);
            }
            if (!textOnly) {
                c.attach(&gd);
            }
            c.notifyObservers(); 
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }
    /*for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Cell &theCell = theGrid[i][j];
            if (!textOnly) {
                theCell.attach(&gd);
                theCell.notifyObservers();
            }
        }
    }*/
    currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();

    vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (Coordinate c : initialCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            theGrid[c.row][c.col].setColour(currentPiece->getColour());
        }
    }
}

bool Grid::inBounds(int i, int j, int maxI, int maxJ) {
    // helper function to find out if a coordinate is in the grid
    return (i < maxI && i >= 0 && j < maxJ && j >= 0);
}

void Grid::print() {
    td.print(currentLevel, score, highScore);
}

void Grid::changeTextOnly() {
    textOnly = true;
}

void Grid::changeGraphicsOnly() {
    graphicsOnly = true;
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
            levelFactory->resetTurnCount();
            ++rowsCleared;
            for (int i = 0; i < width; ++i) {
                Cell &theCell = theGrid[row][i];
                vector<Coordinate> temp =
                theCell.getPiece()->getCoords();
                temp.erase(std::remove(temp.begin(), temp.end(), 
                Coordinate{row,i}), temp.end());
                theCell.getPiece()->setCoords(temp);
                theCell.setColour(Colour::NoColour);
                if (temp.size() == 0) {
                    score += pow(
                    (theCell.getPiece()->getLevelGenerated() + 1), 2);
                }
            }
            dropRows(row);
        }
    }
    if (rowsCleared > 0) {
        score += pow((rowsCleared + currentLevel), 2);
    }
    if (score > highScore) {
        highScore = score;
    }
}

bool Grid::drop() {
    while (shiftPiece(Direction::Down));
    vector<Coordinate> finalCoords = currentPiece->getCoords();
    for (Coordinate c : finalCoords) {
        if (c.row < 3 || !inBounds(c.row, c.col, height, width)) {
            return false;
        }
        theGrid[c.row][c.col].setPiece(currentPiece);
    }
    clearRows();
    if (finalCoords.size() == 1) { // if the piece is a bomb
        return true;
    }
    return (getNextPiece());
}

bool Grid::validMove(vector<Coordinate> newCoords) {
    bool valid = true;
    vector<Coordinate> oldCoords = currentPiece->getCoords();
    for (Coordinate c : oldCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            theGrid[c.row][c.col].setColour(Colour::NoColour);
        } else {
            return false;
        }
    }
    for (Coordinate c : newCoords) {
        if (!inBounds(c.row, c.col, height, width) ||
        theGrid[c.row][c.col].getInfo().colour != Colour::NoColour) {
            valid = false;
            break;
        }
    }
    if (valid) {
        currentPiece->setCoords(newCoords);
    } else {
        for (Coordinate c : oldCoords) {
            theGrid[c.row][c.col].setColour(currentPiece->getColour());
        }
    }
    return valid;
}

bool Grid::heavyMove(vector<Coordinate> moveDown) {
    for (Coordinate &c : moveDown) {
        ++c.row;
    }
    return validMove(moveDown);
}

bool Grid::shiftPiece(Direction d) {
    vector<Coordinate> newPosition = currentPiece->shift(d);
    if (validMove(newPosition)) {
        for (Coordinate c : newPosition) {
            if (inBounds(c.row, c.col, height, width)) {
                theGrid[c.row][c.col].setColour(currentPiece->getColour());
            }
        }
        if (currentPiece->getIsHeavy()) {
            if(heavyMove(newPosition)) {
                for (Coordinate c : newPosition) {
                    theGrid[c.row+1][c.col].setColour(currentPiece->
                    getColour());
                }
            }
        }
        return true;
    }
    return false;
}

bool Grid::rotatePiece(Rotation r) {
    vector<Coordinate> newPosition = currentPiece->rotate(r);
    if (validMove(newPosition)) {
        for (Coordinate c : newPosition) {
            theGrid[c.row][c.col].setColour(currentPiece->getColour());
        }
        return true;
    }
    currentPiece->undoRotation(r);
    return false;
}

bool Grid::getNextPiece() {
    currentPiece = nextPiece;
    nextPiece = levelFactory->generatePiece(); //consider file or random
    vector<Coordinate> newPieceCoords = currentPiece->getCoords();
    for (Coordinate c : newPieceCoords) {
        Cell &theCell = theGrid[c.row][c.col];
        if (theCell.getInfo().colour != Colour::NoColour) {
            return false;
        }
        theCell.setColour(currentPiece->getColour());
    }
    return true;
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
    } else { 
        levelFactory = make_shared<Level0>();
    }
    levelFactory->attach(this);
}

void Grid::levelUp() {
    if (currentLevel < LEVEL_MAX) {
        ++currentLevel;
        updateLevelFactory();
        //cout << "Current level is: " << currentLevel << endl;
        print();
    } else {
        cout << "Level is oustide range of [0,4]" << endl;
    }
}

void Grid::levelDown() {
    if (currentLevel > LEVEL_MIN) {
        --currentLevel;
        updateLevelFactory();
        print();
    } else {
        cout << "Level is oustide range of [0,4]" << endl;
    }
}
void Grid::updateLevel(int lvl) {
    currentLevel = lvl;
    updateLevelFactory();
}

void Grid::updateFileName(string s) {
    if (currentLevel == 0 || currentLevel == 3 || currentLevel == 4) {
        levelFactory->changeFileName(s);
    } else {
        cout << "Level " << currentLevel << " does not allow input file" << endl;
    }
}

void Grid::updateSeed(int x) {
    levelFactory->changeSeed(x);
}

void Grid::restoreRandom() {
    if (currentLevel == 3 || currentLevel == 4) {
        levelFactory->randomize();
    } else {
        if (currentLevel == 0) {
            cout << "Level " << currentLevel << " can not be random" << endl;
        } else {
            cout << "Level " << currentLevel << " is already random" << endl;
        }
    }
}

void Grid::replaceCurrentPiece(string s) {
    vector<Coordinate> oldCoords = currentPiece->getCoords();
    for (Coordinate c : oldCoords) {
        theGrid[c.row][c.col].setColour(Colour::NoColour);
    }
    bool isHeavy = false;
    if (currentLevel > 2) {
        isHeavy = true;
    }
    if (s == "I") {
		currentPiece = make_shared<BlockI>(currentLevel, isHeavy);
	} else if (s == "J") {
		currentPiece = make_shared<BlockJ>(currentLevel, isHeavy);
	} else if (s == "L") {
		currentPiece = make_shared<BlockL>(currentLevel, isHeavy);
	} else if (s == "O") {
		currentPiece = make_shared<BlockO>(currentLevel, isHeavy);
	} else if (s == "S") {
		currentPiece = make_shared<BlockS>(currentLevel, isHeavy);
	} else if (s == "Z") {
		currentPiece = make_shared<BlockZ>(currentLevel, isHeavy);
	} else { //s == "T"
		currentPiece = make_shared<BlockT>(currentLevel, isHeavy);
	}    
    vector<Coordinate> temp = currentPiece->getCoords();
    for (Coordinate c : temp) {
        theGrid[c.row][c.col].setColour(currentPiece->getColour());
    }
}

void Grid::restart() {
    //enter fields of grid that need to be changed when restarted
    turnCount = 0; // MAYBE WE SHOULD REMOVE TURNCOUNT AS A FIELD IT'S NEVER USED LOL
    currentLevel = 0;
    score = 0;
    levelFactory = make_shared<Level0>();
    levelFactory->attach(this);
    currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();
    theGrid.clear();
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}};
            c.attach(&td);
            c.attach(&gd);
            c.notifyObservers();
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }
    vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (Coordinate c : initialCoords) {
        theGrid[c.row][c.col].setColour(currentPiece->getColour());
    }
    print();
}

void Grid::hint() {
    // find out how to implement this
}

bool Grid::notify(Subject<LevelInfo> &from) {
    (void) from;
    shared_ptr<GamePiece> temp = currentPiece;
    currentPiece = make_shared<BlockBomb>();
    Coordinate bombCell = currentPiece->getCoords()[0];
    if (theGrid[bombCell.row][bombCell.col].getInfo().colour !=
    Colour::NoColour) {
        // force drop() to produce false by giving invalid coords
        currentPiece->setCoords(vector<Coordinate>{{-1,-1}}); 
    }
    drop();
    currentPiece = temp;
    return true;
}