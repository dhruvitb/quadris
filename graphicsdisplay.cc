#include "graphicsdisplay.h"
#include "gamepiece.h"
#include "window.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int width, int height):
width{width}, height{height}, squareSize{35} {
    // make a window with extra space to have gaps in the grid
    // plus extra space for the menu
    window = nullptr;
    
}

void GraphicsDisplay::init(string scheme) {
    window = make_unique<Xwindow>(width + pieceSizeOffset + 150,
    height + pieceSizeOffset, scheme);
}

GraphicsDisplay::~GraphicsDisplay() {

}

bool GraphicsDisplay::notify(Subject<CellInfo> &from) {
    CellInfo info = from.getInfo();
    int row = info.row;
    int col = info.col;
    Colour colour = info.colour;
    // convert the colours in our enum class to ints for the window.h class
    int colourValue = (int) colour;
    // make the squares a little bit smaller to make grid effect
    window->fillRectangle(squareSize * col + pieceSizeOffset,
    squareSize * row + pieceSizeOffset, squareSize - pieceSizeOffset,
    squareSize - pieceSizeOffset, colourValue);
    return true;
}

void GraphicsDisplay::updateMenu(int level, int score, int hiScore,
shared_ptr<GamePiece> next, shared_ptr<GamePiece> held) {
    // update the values on the side menu
    if (window) {
        window->fillRectangle(390, 80, 100, 80, 10);
        window->drawString(400, 100, "Level:     " + to_string(level));
        window->drawString(400, 120, "Score:     " + to_string(score));
        window->drawString(400, 140, "Hi Score:  " + to_string(hiScore));
        drawSidePieces(next, held);
    }
}

void GraphicsDisplay::drawSidePieces(shared_ptr<GamePiece> next,
shared_ptr<GamePiece> held) {
    // draw the next piece in queue
    vector<Coordinate> coords = next->getCoords();
    Colour colour = next->getColour();
    int colourValue = (int) colour;
    // cover the area with a white rectangle first
    window->fillRectangle(390, 150, 150, 300, 10);
    window->drawString(400, 200, "Next Piece:");
    for (Coordinate c : coords) {
        window->fillRectangle((c.col * 25) + 405 + pieceSizeOffset, 
        (c.row * 25) + 150 + pieceSizeOffset, 25 - pieceSizeOffset, 
        25 - pieceSizeOffset, colourValue);
    }
    if (held) {
        coords = held->getCoords();
        colour = held->getColour();
        colourValue = (int) colour;
        window->drawString(400, 320, "Held Piece:");
        for (Coordinate c : coords) {
            window->fillRectangle((c.col * 25) + 405 + pieceSizeOffset,
            (c.row * 25) + 270 + pieceSizeOffset, 25 - pieceSizeOffset,
            25 - pieceSizeOffset, colourValue);
        }
    }
}