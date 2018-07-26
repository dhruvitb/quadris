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
    // draw the next and held pieces
    void drawSidePieces(shared_ptr<GamePiece> next, 
    shared_ptr<GamePiece> held); 
public:
    GraphicsDisplay(int width, int height);
    ~GraphicsDisplay();
    // allows for intializing with custom settings (colourscheme)
    void init(std::string scheme);
    bool notify(Subject<CellInfo> &from) override;
    // update the side menu of the display
    void updateMenu(int level, int score, int hiScore, shared_ptr<GamePiece>
    next, shared_ptr<GamePiece> held);
};

#endif
