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
    CellInfo info = from.getInfo();
    int row = info.row;
    int col = info.col;
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
    return true;
}

void TextDisplay::print(int level, int score, int highScore) {
    int width = 11;
    int height = 18;
    cout << "Level:    " << level << endl;
    cout << "Score:    " << score << endl;
    cout << "Hi Score: " << highScore << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << theDisplay[i][j];
        }
        cout << endl;
    }
}