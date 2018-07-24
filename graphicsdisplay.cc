#include "graphicsdisplay.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int height):
width{width}, height{height}, squareSize{35} {
    window = make_unique<Xwindow>(width, height);
}

GraphicsDisplay::~GraphicsDisplay() {

}

bool GraphicsDisplay::notify(Subject<CellInfo> &from) {
    CellInfo info = from.getInfo();
    int row = info.row;
    int col = info.col;
    Colour colour = info.colour;
    int colourValue = (int) colour + 1;
    window->fillRectangle(squareSize * col, squareSize * row, squareSize,
    squareSize, colourValue);
    return true;
}