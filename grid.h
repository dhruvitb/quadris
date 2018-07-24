#ifndef _GRID_H_
#define _GRID_H_
#include "memory"
#include "gamepiece.h"
#include "cell.h"
#include "structures.h"
#include "level.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "observer.h"
#include "X11/Xlib.h"

const int LEVEL_MAX = 4;
const int LEVEL_MIN = 0;

class Grid: public Observer<LevelInfo> {
    const int width = 11;
    const int height = 18;
    int turnCount;
    int currentLevel;
    int score; // score of the current game they're playing
    static int highScore; // instead of keeping highScore in main
    std::vector<std::vector<Cell>> theGrid;
    std::shared_ptr<Level> levelFactory;
    TextDisplay td;
    GraphicsDisplay gd;
    std::shared_ptr<GamePiece> currentPiece;
    std::shared_ptr<GamePiece> nextPiece;
    static bool inBounds(int i, int j, int maxI, int maxJ);
    void updateLevelFactory();
    bool validMove(std::vector<Coordinate> newPosition);
    bool checkClear(int row);
    void clearRows();
    void dropRows(int row);
    bool heavyMove(vector<Coordinate> moveDown);
public:
    ~Grid();
    Grid();
    void print();
    bool drop();
    bool shiftPiece(Direction d);
    bool rotatePiece(Rotation r);
    bool getNextPiece();
    void levelUp();
    void levelDown();
    void updateFileName(std::string f);
    void restoreRandom();
    void replaceCurrentPiece(std::string s);
    void restart();
    void hint();
    bool notify(Subject<LevelInfo> &from) override;
};

#endif