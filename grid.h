#ifndef _GRID_H_
#define _GRID_H_
#include "memory"
#include "gamepiece.h"
#include "cell.h"
#include "structures.h"
#include "level.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

class Grid: public Observer {
    std::vector<std::vector<Cell>> theGrid;
    std::unique_ptr<Level> levelFactory;
    int currentLevel;
    std::unique_ptr<GamePiece> currentPiece;
    std::unique_ptr<GamePiece> nextPiece;
    int turnCount;
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<GraphicsDisplay> gd;
    int score;
public:
    void init();
    void print();
    void drop();
    bool shiftPiece(Direction d);
    bool rotatePiece(Rotation r);
    void nextPiece();
    void changeLevel();
    void gameOver();
    void restart();
    void hint();
};

#endif