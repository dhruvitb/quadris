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
#include "blockhint.h"
#include "gamepiece.h"
#include <set>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include "window.h"
#include "graphicsdisplay.h"
#include "X11/Xlib.h"
using namespace std;

int Grid::highScore = 0;

Grid::Grid(): currentLevel{0}, score{0}, td{}, gd{385, 630} {
    updateLevelFactory();
}

Grid::~Grid() {}

void Grid::init(string scheme) {
    if (!textOnly) {
        gd.init(scheme); // create graphics display with given colour scheme
    }
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}};
            if (!graphicsOnly) {
                c.attach(&td); // only atach text observer if enabled
            }
            if (!textOnly) {
                c.attach(&gd); // only attach graphics observer if enabled
            }
            c.notifyObservers();
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }
    // start off with the current piece and the next piece
    currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();
    vector<Coordinate> initialCoords = currentPiece->getCoords();
    // display the first piece 
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
    // depending on which ones are enabled
    if (!graphicsOnly) {
        td.print(currentLevel, score, highScore, nextPiece, heldPiece);
    }
    if (!textOnly) {
        gd.updateMenu(currentLevel, score, highScore, nextPiece, heldPiece);
    }
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
    removeHint();
    while (shiftPiece(Direction::Down));
    vector<Coordinate> finalCoords = currentPiece->getCoords();
    for (Coordinate c : finalCoords) {
        // if its row is less than 3 it is too high
        if (c.row < 3 || !inBounds(c.row, c.col, height, width)) {
            return false;
        }
        theGrid[c.row][c.col].setPiece(currentPiece);
    }
    clearRows();
    if (finalCoords.size() == 1) { // if the piece is a bomb
        return true;
    }
    // increments turns passed without a line cleared in level 4
    // if a line clears it will be set to 0 by clearRows
    levelFactory->incrementTurnCount(); 
    holdSwapped = false; // player is able to hold a piece since next turn
    return (getNextPiece()); // if a next piece can be given without collision
}

bool Grid::validMove(vector<Coordinate> newCoords, 
shared_ptr<GamePiece> piece) {
    bool valid = true; // will become false if move is not valid 
    vector<Coordinate> oldCoords = piece->getCoords();
    // set its own coordinates to no colour so it doesn't collide with itself
    for (Coordinate c : oldCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            theGrid[c.row][c.col].setColour(Colour::NoColour);
        } else {
            return false;
        }
    }
    // checks for collisions
    for (Coordinate c : newCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            Colour cellColour = theGrid[c.row][c.col].getInfo().colour;
            if  (cellColour!= Colour::NoColour && 
                 cellColour != Colour::Black) {
                valid = false;
                break;
            }
        } else {
            valid = false;
            break;
        }
    }
    // give the piece it's new coordinates
    if (valid) {
        piece->setCoords(newCoords);
        removeHint();
    } else { // otherwise keep old coordinates and add colours back 
        for (Coordinate c : oldCoords) {
            theGrid[c.row][c.col].setColour(piece->getColour());
        }
    }
    return valid; // return if successful
}

bool Grid::heavyMove(vector<Coordinate> moveDown) {
    // move the piece down one if row (if valid)
    for (Coordinate &c : moveDown) {
        ++c.row;
    }
    return validMove(moveDown, currentPiece);
}

bool Grid::shiftPiece(Direction d, shared_ptr<GamePiece> piece) {
    if (!piece) {
        // have to do it this way since it won't allow currentPiece as a 
        // default parameter
        piece = currentPiece;
    }
    vector<Coordinate> newPosition = piece->shift(d);
    // check if valid, if it is set colours and notify observers
    if (validMove(newPosition, piece)) {
        for (Coordinate c : newPosition) {
            if (inBounds(c.row, c.col, height, width)) {
                theGrid[c.row][c.col].setColour(piece->getColour());
            }
        }
        // if piece is heavy, move it down 1
        if (piece->getIsHeavy()) {
            if(heavyMove(newPosition)) {
                for (Coordinate c : newPosition) {
                    theGrid[c.row + 1][c.col].setColour(piece->
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
    // check for valid rotation and update colours
    if (validMove(newPosition, currentPiece)) {
        for (Coordinate c : newPosition) {
            theGrid[c.row][c.col].setColour(currentPiece->getColour());
        }
        // move down one row if heavy
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
    // get the next piece and set it to the current piece
    currentPiece = nextPiece;
    nextPiece = levelFactory->generatePiece(); //consider file or random
    vector<Coordinate> newPieceCoords = currentPiece->getCoords();
    for (Coordinate c : newPieceCoords) {
        Cell &theCell = theGrid[c.row][c.col];
        if (theCell.getInfo().colour != Colour::NoColour &&
            theCell.getInfo().colour != Colour::Black) {
            return false; // used in game over check
        }
        // update the colours to show the next peice
        theCell.setColour(currentPiece->getColour());
    }
    return true;
}

void Grid::updateLevelFactory() {
    // maps the integer level to a level factory
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
    // level up if valid
    if (currentLevel < LEVEL_MAX) {
        ++currentLevel;
        updateLevelFactory();
        print();
    } else {
        cout << "Level is outside range of [" << 
        LEVEL_MIN << "," << LEVEL_MAX << "]" << endl;
    }
}

void Grid::levelDown() {
    // level down if valid
    if (currentLevel > LEVEL_MIN) {
        --currentLevel;
        updateLevelFactory();
        print();
    } else {
        cout << "Level is outside range of [" << 
        LEVEL_MIN << "," << LEVEL_MAX << "]" << endl;
    }
}
void Grid::updateLevel(int lvl) {
    // used to set a particular level
    currentLevel = lvl;
    updateLevelFactory();
}

void Grid::updateFileName(string s) {
    // only for levels that allow files
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
        cout << "Level 0 cannot have a seed" << endl;
    }
}

void Grid::restoreRandom() {
    if (currentLevel == 3 || currentLevel == 4) {
        levelFactory->randomize();
    } else {
        if (currentLevel == 0) {
            cout << "Level " << currentLevel << " cannot be random" << endl;
        } else {
            cout << "Level " << currentLevel << " is already random" << endl;
        }
    }
}

shared_ptr<GamePiece> Grid::createPiece(string s, int levelGenerated, 
bool isHeavy) {
    shared_ptr<GamePiece> newPiece;
    if (s == "I") {
		newPiece = make_shared<BlockI>(levelGenerated, isHeavy);
	} else if (s == "J") {
		newPiece = make_shared<BlockJ>(levelGenerated, isHeavy);
	} else if (s == "L") {
		newPiece = make_shared<BlockL>(levelGenerated, isHeavy);
	} else if (s == "O") {
		newPiece = make_shared<BlockO>(levelGenerated, isHeavy);
	} else if (s == "S") {
		newPiece = make_shared<BlockS>(levelGenerated, isHeavy);
	} else if (s == "Z") {
		newPiece = make_shared<BlockZ>(levelGenerated, isHeavy);
	} else { //s == "T"
		newPiece = make_shared<BlockT>(levelGenerated, isHeavy);
	}   
    return newPiece;
}

void Grid::replaceCurrentPiece(string s, int levelGenerated, bool isHeavy) {

    shared_ptr<GamePiece> newPiece = createPiece(s, levelGenerated, isHeavy);
    //only makes changes if the block are different
    if (currentPiece->getColour() != newPiece->getColour()) {
        bool replaceable = true;
        Coordinate lowerLeft = currentPiece->getLowerLeft();
        Coordinate lowerLeftTemplate {4,0}; //by our own definition
        if (newPiece->getSymbol() == 'I') {
            if (lowerLeft.col > 7) {
                replaceable = false;
            }
            lowerLeftTemplate.row = 3;
        }
        Coordinate offset = lowerLeft - lowerLeftTemplate;
        vector<Coordinate> temp = newPiece->getCoords();
        //increment temp by offset coordinates
        for (Coordinate &c : temp) {
            c = c + offset;
        }
        newPiece->setCoords(temp);
        //checks to make sure the replacement coordinates is possible
        //first remove colour from old coordinates
        vector<Coordinate> oldCoords = currentPiece->getCoords();
        for (Coordinate c : oldCoords) {
            theGrid[c.row][c.col].setColour(Colour::NoColour);
        }
        //then check the colour of the new coordinates
        for (Coordinate c : newPiece->getCoords()) {
            Cell &theCell = theGrid[c.row][c.col];
            Colour cellColour = theCell.getInfo().colour;
            if (!(inBounds(c.row, c.col, height, width)) ||
                (cellColour != Colour::NoColour &&
                 cellColour != Colour::Black )) {
                replaceable = false;
                break;
            }
        }
        if (replaceable) {
            currentPiece = newPiece;
            //add colour to new coordinates
            for (Coordinate c : currentPiece->getCoords()) {
                theGrid[c.row][c.col].setColour(currentPiece->getColour());
            }
        } else {
            cout << "Invalid command: block cannot fit" << endl;

            //put the colour of the original piece back
            for (Coordinate c : oldCoords) {
                theGrid[c.row][c.col].setColour(currentPiece->getColour());
            }    
        }
    } 
}

void Grid::restart() {
    //enter fields of grid that need to be changed when restarted
    currentLevel = 0;
    score = 0;
    levelFactory = make_shared<Level0>(); // level becomes 0 again
    levelFactory->attach(this);
    currentPiece = levelFactory->generatePiece();
    nextPiece = levelFactory->generatePiece();
    theGrid.clear(); // empty the cells of the grid
    heldPiece = nullptr; // reset the held piece
    holdSwapped = false; // allow them to swap on the first turn
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
    shared_ptr<GamePiece> theHint = make_shared<BlockHint>();
    //give hintPiece the necessary fields from currentPiece
    theHint->setCoords(currentPiece->getCoords());
    theHint->setRotationIndex(currentPiece->getRotationIndex());
    //keeps a copy of current piece coordinates
    vector<Coordinate> copyCurrentCoords = currentPiece->getCoords();
    //removes colour from the cells
    for (Coordinate c : copyCurrentCoords) {
        theGrid[c.row][c.col].setColour(Colour::NoColour);
    }
    //find the optimal column for hint 
    int furthestCol = width - 3; 
    if (currentPiece->getSymbol() == 'I') { //special case for I
        furthestCol = width - 4;
    } 
    int randomCol = rand() % furthestCol; //random column for left side of block
    int offset = currentPiece->getLowerLeft().col - randomCol;
    //update thehint piece with the offset amount
    vector<Coordinate> hintCoords = theHint->getCoords();
    for (Coordinate &c : hintCoords) {
        c.col = c.col - offset;
    }
    theHint->setCoords(hintCoords);
    while (shiftPiece(Direction::Down, theHint));
    //set the hintPiece to theHint
    hintPiece = theHint;
    //give the cell the hint piece
    hintCoords = hintPiece->getCoords();
    for (Coordinate c : hintCoords) {
        if (inBounds(c.row, c.col, height, width)) {
            theGrid[c.row][c.col].setPiece(theHint);
            theGrid[c.row][c.col].setColour(theHint->getColour());
        }
    }
    //add colour of current cell back to cells
    for (Coordinate c : copyCurrentCoords) {
        theGrid[c.row][c.col].setColour(currentPiece->getColour());
    }
}

bool Grid::notify(Subject<LevelInfo> &from) {
    // drop a bomb in the center
    (void) from;
    shared_ptr<GamePiece> temp = currentPiece;
    currentPiece = make_shared<BlockBomb>();
    Coordinate bombCell = currentPiece->getCoords()[0];
    Colour cellColour = theGrid[bombCell.row][bombCell.col].getInfo().colour;
    if (cellColour != Colour::NoColour && cellColour != Colour::Black) {
        // force drop() to produce false by giving invalid coords
        currentPiece->setCoords(vector<Coordinate>{{-1,-1}});
    }
    drop();
    currentPiece = temp;
    return true;
}

bool Grid::hold() {
    if (holdSwapped) {
        cout << "You've already held a piece this turn" << endl;
        return true;
    }
    // make a temp copy of the currentPiece to swap
    string currentPieceName;
    currentPieceName.push_back(currentPiece->getSymbol());
    shared_ptr<GamePiece> temp = createPiece(currentPieceName, 
    currentPiece->getLevelGenerated(), currentPiece->getIsHeavy());
    if (heldPiece) { // if there is already a held piece, swap 
        vector<Coordinate> oldCoords = currentPiece->getCoords();
        vector<Coordinate> heldCoords = heldPiece->getCoords();
        for (Coordinate c : oldCoords) {
            theGrid[c.row][c.col].setColour(Colour::NoColour);
        }
        for (Coordinate c : heldCoords) {
            Cell &theCell = theGrid[c.row][c.col];
            Colour cellColour = theCell.getInfo().colour;
            if (cellColour != Colour::NoColour && 
                cellColour != Colour::Black) {
                // if not swappable you lose since you've hit the top
                // with the piece
                return false; 
            }
            theCell.setColour(heldPiece->getColour());
        }
        string heldPieceName;
        heldPieceName.push_back(heldPiece->getSymbol());
        currentPiece = createPiece(heldPieceName, 
        heldPiece->getLevelGenerated(), heldPiece->getIsHeavy());
        heldPiece = temp;
        holdSwapped = true;
    } else { // if this is the first time, i.e. heldPiece is nullptr
        vector<Coordinate> tempCoords = currentPiece->getCoords();
        for (Coordinate c : tempCoords) {
            theGrid[c.row][c.col].setColour(Colour::NoColour);
        }
        getNextPiece();
        heldPiece = temp;
    }
    print();
    return true;
}

void Grid::removeHint() {
    // remove the hint block
    if (hintPiece != nullptr) {
        vector<Coordinate> hintCoords = hintPiece->getCoords();
        for (Coordinate c : hintCoords) {
            Cell &theCell = theGrid[c.row][c.col];
            theCell.setColour(Colour::NoColour);
            theCell.setPiece(nullptr);
        }
        hintPiece = nullptr;
    }
}

int Grid::getCurrentLevel() {
    return currentLevel;
}
