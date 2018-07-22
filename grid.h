#ifndef _GRID_H_
#define _GRID_H_
#include "memory"
#include "gamepiece.h"
#include "cell.h"
#include "structures.h"
#include "level.h"
#include "textdisplay.h"
//#include "graphicsdisplay.h"
#include "observer.h"

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
    std::shared_ptr<TextDisplay> td;
    //std::unique_ptr<GraphicsDisplay> gd;
    std::shared_ptr<GamePiece> currentPiece;
    std::shared_ptr<GamePiece> nextPiece;
    static bool inBounds(int i, int j, int maxI, int maxJ);
    void incrementLevel();
    void decrementLevel();
    bool movePiece(std::vector<Coordinate> newPosition);
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