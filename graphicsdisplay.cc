#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int height):
width{width}, height{height}, squareSize{35} {
    // make a window with extra space to have gaps in the grid
    // plus extra space for the menu
    window = make_unique<Xwindow>(width + pieceSizeOffset + 150,
    height + pieceSizeOffset);
}

GraphicsDisplay::~GraphicsDisplay() {

}

bool GraphicsDisplay::notify(Subject<CellInfo> &from) {
    CellInfo info = from.getInfo();
    int row = info.row;
    int col = info.col;
    Colour colour = info.colour;
    // convert the colours in our enum class to ints for the window.h class
    int colourValue = (int) colour + 1;
    // make the squares a little bit smaller to make grid effect
    window->fillRectangle(squareSize * col + pieceSizeOffset,
    squareSize * row + pieceSizeOffset, squareSize - pieceSizeOffset,
    squareSize - pieceSizeOffset, colourValue);
    return true;
}

void GraphicsDisplay::updateMenu(int level, int score, int hiScore) {
    window->fillRectangle(390, 80, 100, 80, 0);
    window->drawString(400, 100, "Level:     " + to_string(level));
    window->drawString(400, 120, "Score:     " + to_string(score));
    window->drawString(400, 140, "Hi Score:  " + to_string(hiScore));
}