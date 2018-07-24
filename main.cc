#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>
#include "grid.h"
#include "gamepiece.h"

using namespace std;

int main(int argc, char *argv[]) {
    (void) argc; // REMOVE THESE ONCE YOU ACTUALLY MAKE USE OF THEM MAYBE LAMDLKANVJISFNLVKSJFDNVLKV
    (void) argv; // REMOVE THESE ONCE YOU ACTUALLY MAKE USE OF THEM MAYBE LAMDLKANVJISFNLVKSJFDNVLKV
    // FIND OUT HOW TO READ -ARG N TYPE COMMAND LINE ARGUMENTS
    unique_ptr<Grid> quadris = make_unique<Grid>();
    ifstream commandFile;

    while (true) {
        string cmd;
        if(commandFile) {
            commandFile >> cmd;
            if(cmd == "") {
                commandFile.close();
                //assert(!commandFile);
            } /*else {
                cout << "[from sequence file] " << cmd << endl;
            }*/
        }
        if (!commandFile) {
            cin >> cmd;
            if (cmd == "") {
                break;
            }
        }
        if (cmd == "start") {
            quadris->print();
        } else if (cmd == "left" || cmd == "l") {
            quadris->shiftPiece(Direction::Left);
            quadris->print();
            // move the current piece left
        } else if (cmd == "right" || cmd == "r") {
            quadris->shiftPiece(Direction::Right);
            quadris->print();
            // move the current piece right
        } else if (cmd == "down" || cmd == "d") {
            quadris->shiftPiece(Direction::Down);
            quadris->print();
            // move the current piece down
        } else if (cmd == "clockwise" || cmd == "cw") {
            quadris->rotatePiece(Rotation::CW);
            quadris->print();
            // rotate 90 degrees clockwise
        } else if (cmd == "counterclockwise" || cmd == "ccw") {
            quadris->rotatePiece(Rotation::CCW);
            quadris->print();
            // rotate 90 degrees counterclockwise
        } else if (cmd == "drop") {
            if (!quadris->drop()) {
                cout << "Game Over! Keep playing? Y/N" << endl;
                string answer;
                while (true) {
                    cin >> answer;
                    transform(answer.begin(), answer.end(),
                    answer.end(), ::tolower);
                    if (answer == "y" || answer == "yes") {
                        quadris->restart();
                        break;
                    } else if (answer == "n" || answer == "no") {
                        answer = "endGame";
                        break;
                    }
                }
                if (answer == "endGame") {
                    break;
                }
            }
            quadris->print();
            // drop the piece, summon next one (the drop function handles this)
        } else if (cmd == "levelup") {
            quadris->levelUp();
            // increment level if possible
        } else if (cmd == "leveldown") {
            quadris->levelDown();
            // decrement level if possible
        } else if (cmd == "norandom") {
            string s;
            try {
                cin >> s;
                quadris->updateFileName(s);
            } catch(...) {
                cout << "Invalid file." << endl;
            }
            // if level is 3/4 make it read from fileName
            // finish the try catch block above*****
        } else if (cmd == "random") {
            quadris->restoreRandom();
            // if level is 3/4 restore randomness
        } else if (cmd == "sequence") {
            string fileName;
            cin >> fileName;

            commandFile.open(fileName);
            if (!commandFile) {
                cout << "invalid file :(" << endl;
            }
            // execute sequence of commands in fileName
        } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O"
        || cmd == "S" || cmd == "T" || cmd == "Z") {
            quadris->replaceCurrentPiece(cmd);
            quadris->print();
            // change the current block to the block
        } else if (cmd == "restart") {
            // clear the board and start new game
            quadris->restart();
        } else if (cmd == "hint") {
            // display a hint
        } else {
            cout << "Invalid command: " << cmd << endl;
        }
    }
}