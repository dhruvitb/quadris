#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include "grid.h"
#include "gamepiece.h"
#include "X11/Xlib.h"
#include "graphicsdisplay.h"

using namespace std;

//checks if command contains action and ensures the command is valid
//there may be a multiplier
bool validCommand(string command, string action) {
    bool contains = command.find(action);
    cout << contains << endl;
    bool valid;
    stringstream ss(command);
    int n;
    string s;
    ss >> n >> s;
    cout << "multiplier is: " << n << endl;
    cout << "command is: " << s << endl;
    cout << "action is: " << action << endl;
    if (n >= 0 && s == action) {
        valid = true;
    }
    cout << valid << endl;
    return contains && valid;
}

//finds the multiplier
int multiplier(string command, string action) {
}

int main(int argc, char *argv[]) {
    unique_ptr<Grid> quadris = make_unique<Grid>();
    ifstream commandFile;
    //startlevel is separate because scriptfile and seed depend on the level
    for (int i = 1; i < argc; ++i) {
        string option = argv[i];
        if (option == "-startlevel") {
            string lvl = argv[i+1];
            stringstream ss(lvl); //convert from string to int
            int x;
            ss >> x;
            quadris->updateLevel(x);
            ++i;
            //change the level
        }
    }
    for (int i = 1; i < argc; ++i) {
        string option = argv[i];
        if (option == "-text") {
            quadris->changeTextOnly();
        } else if (option == "graphics") {
            quadris->changeGraphicsOnly();
        }else if (option == "-seed") {
            string seed = argv[i+1];
            stringstream ss(seed); //convert from string to int
            int x;
            ss >> x;
            ++i;
            quadris->updateSeed(x);
            //do something with seed
        } else if (option == "-scriptfile") {
            string file = argv[i+1]; //changes default file for level 0
            ++i;
            quadris->updateFileName(file);
            //do something with file
        } 
    }
    quadris->init(); //considers command-line interface
    quadris->print();

    while (true) {
        string cmd;
        if(commandFile) {
            commandFile >> cmd;
            if(cmd == "") { //means file has reached EOF
                commandFile.close();
            }
        }
        if (!commandFile) {
            cin >> cmd;
            if (cmd == "") { //no more user input so end program
                break;
            }
        }
        if (validCommand(cmd, "left")) {
            quadris->shiftPiece(Direction::Left);
            quadris->print();
            // move the current piece left
        } else if (validCommand(cmd, "right")) {
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
                cout << "Invalid file: " << fileName << " :(" << endl;
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