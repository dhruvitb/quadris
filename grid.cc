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

Grid::Grid(): currentLevel{0}, score{0}, td{}, gd{385, 630} {
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
    td.print(currentLevel, score, highScore, nextPiece);
    gd.updateMenu(currentLevel, score, highScore, nextPiece);
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
            return false; // if one of the cells does not have a piece in it
        }
    }
    return true;
}

void Grid::dropRows(int row) {
    while (row > 0) {
        for (int i = 0; i < width; ++i) {
            // clear the previous row
            theGrid[row-1][i].setColour(Colour::NoColour);
            // get the piece that occupies the cell in the previous row
            shared_ptr<GamePiece> cellsPiece = theGrid[row-1][i].getPiece();
            if (cellsPiece) { // if there is a piece on the cell
                vector<Coordinate> temp = cellsPiece->getCoords();
                for (Coordinate &c : temp) {
                    if (c.row == row - 1) {
                        // update the coordinates in the previous row to be in
                        // this row, and remove the pointer from the old 
                        // coordinate and add to the cell below it
                        c.row = row;
                        theGrid[row-1][c.col].setPiece(nullptr); 
                        theGrid[row][c.col].setPiece(cellsPiece);
                    }
                    // update the colour of the cell
                    theGrid[c.row][c.col].setColour(cellsPiece->getColour());
                }
                // change coords of piece to match its location displayed
                cellsPiece->setCoords(temp);
            }
        }
        --row;
    }
}

void Grid::clearRows() {
    vector<Coordinate> finalCoords = currentPiece->getCoords();
    set<int> rowsSpanned; // every unique row that might need to be cleared
    int rowsCleared = 0; // number of rows cleared at once
    for (Coordinate coord : finalCoords) {
        rowsSpanned.insert(coord.row);
    }
    for (int row : rowsSpanned) {
        if (checkClear(row)) {
            // since we have cleared a row, we reset the brick piece counter 
            // in levelFactory 
            levelFactory->resetTurnCount();
            ++rowsCleared;
            for (int i = 0; i < width; ++i) {
                Cell &theCell = theGrid[row][i];
                // remove the coordinate of the cell being cleared from the 
                // list of coordinates in the related piece
                vector<Coordinate> temp =
                theCell.getPiece()->getCoords();
                temp.erase(std::remove(temp.begin(), temp.end(), 
                Coordinate{row,i}), temp.end());
                theCell.getPiece()->setCoords(temp); // set the new coords
                theCell.setColour(Colour::NoColour); // make colour blank
                if (temp.size() == 0) { // if the piece has been cleared
                    score += pow(
                    (theCell.getPiece()->getLevelGenerated() + 1), 2);
                }
            }
            dropRows(row); // drop the rows above the row that was cleared
        }
    }
    if (rowsCleared > 0) { // calculate scores if rows were cleared
        score += pow((rowsCleared + currentLevel), 2);
    }
    if (score > highScore) {
        highScore = score; // keep highscore updated
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
    levelFactory->incrementTurnCount();
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
        if (currentPiece->getIsHeavy()) {
            if(heavyMove(newPosition)) {
                for (Coordinate c : newPosition) {
                    theGrid[c.row + 1][c.col].setColour(currentPiece->
                    getColour());
                }
            }
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
        cout << "Level is outside range of [0,4]" << endl;
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
        cout << "Level " << currentLevel << 
        " does not allow input file" << endl;
    }
}

void Grid::updateSeed(int x) {
    if (currentLevel != 0) {
        levelFactory->changeSeed(x);
    } else {
        cout << "Level 0 can not have a seed" << endl;
    }
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
    cout << "You are restarting at level 0" << endl;
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