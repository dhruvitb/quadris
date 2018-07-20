#include "grid.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
using namespace std;

Grid::~Grid() {

}

bool Grid::inBounds(int i, int j, int maxI, int maxJ) {
    // helper function to find out if a coordinate is in the grid
    return (i < maxI && i >= 0 && j < maxJ && j >= 0);
}

void Grid::init() {
    currentLevel = 0;
    turnCount = 0; // or should we make it one?
    score = 0;
    //currentPiece = levelFactory->generatePiece();
    //nextPiece = levelFactory->generatePiece();
    td = make_unique<TextDisplay>();
    //unique_ptr<GraphicsDisplay> gd = make_unique<GraphicsDisplay>();
    //unique_ptr<Level> levelFactory = make_unique<Level0>();
    int width = 11;
    int height = 18;
    for (int i = 0; i < height; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < width; ++j) {
            Cell c = Cell{Coordinate{i,j}, Colour::NoColour};
            temp.emplace_back(c);
        }
        theGrid.emplace_back(temp);
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // attach the up and right cell as observer
            if (inBounds(i - 1, j, height, width)) {
                theGrid[i][j].attachObserver(theGrid[i - 1][j]);
            }
            if (inBounds(i, j + 1, height, width)) {
                theGrid[i][j].attachObserver(theGrid[i][j + 1]);
            }
        }
    }
}

void Grid::print() {
    td->print();
}

void Grid::drop() {
    currentPiece->drop();
}

bool Grid::shiftPiece(Direction d) {
    currentPiece->shift(d);
    return true; // FIX THIS PLEASE
}

bool Grid::rotatePiece(Rotation r) {
    currentPiece->rotate(r);
    return true; // FIX THIS PLEASE
}

void Grid::getNextPiece() {
    currentPiece = nextPiece;
    nextPiece = levelFactory->generatePiece();
}

void Grid::incrementLevel() {
    if (currentLevel == 0) {
        levelFactory = make_unique<Level1>();
    } else if (currentLevel == 1) {
        levelFactory = make_unique<Level2>();
    } else if (currentLevel == 2) {
        levelFactory = make_unique<Level3>();
    } else { // changeLevel checks if the level is in bounds 
        levelFactory = make_unique<Level4>();
    }
}

void Grid::decrementLevel() {
    if (currentLevel == 4) {
        levelFactory = make_unique<Level3>();
    } else if (currentLevel == 3) {
        levelFactory = make_unique<Level2>();
    } else if (currentLevel == 2) {
        levelFactory = make_unique<Level1>();
    } else { // changeLevel checks if the level is in bounds
        levelFactory = make_unique<Level0>(); 
    }
}

void Grid::changeLevel() {
    if (currentLevel < LEVEL_MAX) {
        ++currentLevel;
        incrementLevel();
    } else if (currentLevel > LEVEL_MIN) {
        --currentLevel;
        decrementLevel();
    }
}

void Grid::gameOver() {
    // find out how to implement this
}

void Grid::restart() {
    init();
}

void Grid::hint() {
    // find out how to implement this
}

int Grid::getScore() {
    return score;
}