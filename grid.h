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

const int LEVEL_MAX = 4;
const int LEVEL_MIN = 0;

class Grid: public Observer<LevelInfo> {
    int turnCount;
    int currentLevel;
    int score;
    static int highScore;
    std::vector<std::vector<Cell>> theGrid;
    std::unique_ptr<Level> levelFactory;
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<GraphicsDisplay> gd;
    std::shared_ptr<GamePiece> currentPiece;
    std::shared_ptr<GamePiece> nextPiece;
    static bool inBounds(int i, int j, int maxI, int maxJ);
    void incrementLevel();
    void decrementLevel();
public:
    ~Grid();
    void init();
    void print();
    void drop();
    bool shiftPiece(Direction d);
    bool rotatePiece(Rotation r);
    void getNextPiece();
    void changeLevel();
    void gameOver();
    void restart();
    void hint();
    int getScore();
    bool notify(Subject<LevelInfo> &from) override;
};

#endif