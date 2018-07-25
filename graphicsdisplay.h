#ifndef _GRAPHICS_DISPLAY_H_
#define _GRAPHICS_DISPLAY_H_
#include "observer.h"
#include "window.h"
#include "structures.h"
#include "subject.h"
#include "gamepiece.h"
#include <memory>

class GraphicsDisplay: public Observer<CellInfo> {
    unique_ptr<Xwindow> window;
    int width; // width of the window
    int height; // height of the window
    int squareSize; // size of the squares to be drawn
    int pieceSizeOffset = 2; // distance between pieces (to give grid effect)
    void drawNext(shared_ptr<GamePiece> next); // show next piece
public:
    GraphicsDisplay(int width, int height);
    ~GraphicsDisplay();
    bool notify(Subject<CellInfo> &from);
    void updateMenu(int level, int score, int hiScore, shared_ptr<GamePiece>
    next);
    void removeWindow();
    void changeColourScheme(std::string s);
};

#endif