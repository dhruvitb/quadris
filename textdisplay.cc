#include "textdisplay.h"
#include "iostream"
#include "gamepiece.h"
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
        theDisplay[row][col] = I;
    } else if (colour == Colour::Blue) {
        theDisplay[row][col] = J;
    } else if (colour == Colour::Orange) {
        theDisplay[row][col] = L;
    } else if (colour == Colour::Yellow) {
        theDisplay[row][col] = O;
    } else if (colour == Colour::Green) {
        theDisplay[row][col] = S;
    } else if (colour == Colour::Red) {
        theDisplay[row][col] = Z;
    } else if (colour == Colour::Purple) {
        theDisplay[row][col] = T;
    } else if (colour == Colour::NoColour) {
        theDisplay[row][col] = BLANK;
    } else if (colour == Colour::Brown) {
        theDisplay[row][col] = BOMB;
    }
    return true;
}

void TextDisplay::print(int level, int score, int hiScore, 
shared_ptr<GamePiece> next) {
    int width = 11;
    int height = 18;
    cout << "Level:    " << level << endl;
    cout << "Score:    " << score << endl;
    cout << "Hi Score: " << hiScore << endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << theDisplay[i][j];
        }
        cout << endl;
    }
    cout << "Next Piece:" << std::endl;
    vector<Coordinate> coords = next->getCoords();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            bool isOccupied = false;
            Coordinate temp = Coordinate{i + 3, j};
            for (Coordinate c : coords) {
                if (temp == c) {
                    cout << next->getSymbol();
                    isOccupied = true;
                }
            }
            if (!isOccupied) {
                cout << " ";
            }
        }
        cout << endl;
    }
}