#include "textdisplay.h"
#include "iostream"
using namespace std;

TextDisplay::TextDisplay() {
    int width = 11;
    int height = 18;
    for (int i = 0; i < height; ++i) {
        vector<char> temp;
        for (int j = 0; j < width; ++j) {
            temp.emplace_back(BLANK);
        }
        theDisplay.emplace_back(temp);
    }
}

bool TextDisplay::notify(Subject<CellInfo> &from) {
    
}

bool TextDisplay::notify(Subject<CellInfo> &from) {
    CellInfo info = from.getInfo();
    int row = info.y;
    int col = info.x;
    Colour colour = info.colour;
    if (colour == Colour::Cyan) {
        theDisplay[col][row] = I;
    } else if (colour == Colour::Blue) {
        theDisplay[col][row] = J;
    } else if (colour == Colour::Orange) {
        theDisplay[col][row] = L;
    } else if (colour == Colour::Yellow) {
        theDisplay[col][row] = O;
    } else if (colour == Colour::Green) {
        theDisplay[col][row] = S;
    } else if (colour == Colour::Red) {
        theDisplay[col][row] = Z;
    } else if (colour == Colour::Purple) {
        theDisplay[col][row] = T;
    }
}

void TextDisplay::print() {
    int width = 11;
    int height = 18;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << theDisplay[i][j];
        }
        cout << endl;
    }
}