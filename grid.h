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
    int currentLevel; // currentLevel 
    int score; // score of the current game they're playing
    static int highScore; // instead of keeping highScore in main
    std::vector<std::vector<Cell>> theGrid; // the grid
    std::shared_ptr<Level> levelFactory; // the level used to generate pieces
    TextDisplay td; // the text display
    bool textOnly; // changed by command line arguments
    GraphicsDisplay gd; // graphics display
    bool graphicsOnly; // changed by command line arguments
    std::shared_ptr<GamePiece> currentPiece; // the current piece on the board
    std::shared_ptr<GamePiece> nextPiece; // the next piece in the queue
    std::shared_ptr<GamePiece> hintPiece; //filled when hint is called
    std::shared_ptr<GamePiece> heldPiece;
    // returns whether a Coordinate is within the bounds of the board
    static bool inBounds(int i, int j, int maxI, int maxJ); 
    // changes the levelFactor to be equal to the changed level
    void updateLevelFactory();
    // checks each coordinate in newPosition to see if it's valid
    bool validMove(std::vector<Coordinate> newPosition);
    // returns true if a line can be cleared (if it's filled)
    bool checkClear(int row);
    // clears rows if they are filled
    void clearRows();
    // drops down the board after a row clear
    void dropRows(int row);
    // moves a piece down after a move on heavy turns
    bool heavyMove(vector<Coordinate> moveDown);
    // if the player has already swapped with the held piece this turn
    bool holdSwapped = false;
    // helper for replaceCurrentPiece
    shared_ptr<GamePiece> createPiece(std::string s, 
    int levelGenerated, bool isHeavy);

public:
    ~Grid();
    Grid();
    void init(std::string scheme); //attaches gd, sets level
    void print(); // updates & prints textDisplay and graphicsDisplay
    void changeTextOnly(); // toggles text-only mode
    void changeGraphicsOnly(); // toggles graphics-only mode
    bool drop(); // drops current piece
    bool shiftPiece(Direction d); // moves current piece in given direction
    bool rotatePiece(Rotation r); // rotates current piece in given rotation
    bool getNextPiece(); // gets the next piece from the levelFactory
    void levelUp(); // increases the level if possible
    void levelDown(); // decreases the level if possible
    void updateLevel(int lvl); // changes the level to be lvl
    void updateFileName(std::string f); // adds a file to read from???????????????????????????????????????
    void updateSeed(int x); // changes the seed for block generation to x
    void restoreRandom(); // restores randomness to a level
    // replaces current piece with s keeping the position of lower left
    void replaceCurrentPiece(std::string s, int levelGenerated, bool isHeavy);
    int getCurrentLevel();
    void restart(); // reinitializes the game (saves high score)
    void hint(); // displays a hint for current piece
    bool hold(); // holds the current piece for later use
    bool notify(Subject<LevelInfo> &from) override; // receives notification
};

#endif