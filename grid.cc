#include "grid.h"
#include <vector>
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "blockbomb.h"
using namespace std;

Grid::~Grid() {

}

bool Grid::inBounds(int i, int j, int maxI, int maxJ) {
    // helper function to find out if a coordinate is in the grid
    return (i < maxI && i >= 0 && j < maxJ && j >= 0);
}

int Grid::highScore = 0;

void Grid::init() {
    turnCount = 1; // should we make this 0?
    currentLevel = 0;
    score = 0;
    levelFactory = make_shared<Level0>();
    //levelFactory->attach(make_shared<Observer>(this));
    td = make_shared<TextDisplay>();
    //gd = make_unique<GraphicsDisplay>();
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
            theGrid[i][j].attach(td);
            if (inBounds(i - 1, j, height, width)) {
                theGrid[i][j].attach(make_shared<Cell>(theGrid[i-1][j]));
            }
            if (inBounds(i, j + 1, height, width)) {
                theGrid[i][j].attach(make_shared<Cell>(theGrid[i][j+1]));
            }
        }
    }
    vector<Coordinate> initialCoords = currentPiece->getCoords();
    for (auto coord : initialCoords) {
        theGrid[coord.col][coord.row].setColour(currentPiece->getColour());
        cout << "Colour the coord: " << coord.col << " " << coord.row << endl;
    }
}

void Grid::print() {
    td->print(currentLevel, score, highScore);
}

void Grid::drop() {
    while (shiftPiece(Direction::Down));
}

bool Grid::movePiece(vector<Coordinate> newPosition) {
    int size = newPosition.size();
    bool valid = true;
    for (int i = 0; i < size; ++i) {
        int row = newPosition[i].row;
        int col = newPosition[i].col;
        if (!inBounds(row, col, height, width)) {
            valid = false;
            break;
        }
        if (theGrid[row][col].getInfo().colour != Colour::NoColour) {
            valid = false;
            break;
        }
    }
    if (valid) {
        currentPiece->setCoords(newPosition);
    }
    return valid;
}

bool Grid::shiftPiece(Direction d) {
    vector<Coordinate> newPosition = currentPiece->shift(d);
    return movePiece(newPosition);
}

bool Grid::rotatePiece(Rotation r) {
    vector<Coordinate> newPosition = currentPiece->rotate(r);
    return movePiece(newPosition);
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
    // it will probably call restart
}

void Grid::restart() {
    if (score > this->highScore) {
        highScore = score;
    }
    init();
}

void Grid::hint() {
    // find out how to implement this
}

int Grid::getScore() {
    return score;
}

bool Grid::notify(Subject<LevelInfo> &from) {
    if (from.getInfo().dropBomb) {
        // switch the current piece to a bomb, drop it, switch back
        shared_ptr<GamePiece> temp = currentPiece;
        currentPiece = make_shared<BlockBomb>();
        drop();
        currentPiece = temp;
    }
    return true;
}