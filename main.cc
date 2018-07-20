#include <iostream>
#include <string>
#include <vector>
#include "gamepiece.h"

using namespace std;

int main(int argc, char *argv[]) {
    string cmd;
    // FIND OUT HOW TO READ -ARG N TYPE COMMAND LINE ARGUMENTS
    int highScore = 0;
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "left") {
                // move the current piece left
            } else if (cmd == "right") {
                // move the current piece right
            } else if (cmd == "down") {
                // move the current piece down
            } else if (cmd == "clockwise") {
                // rotate 90 degrees clockwise
            } else if (cmd == "counterclockwise") {
                // rotate 90 degrees counterclockwise
            } else if (cmd == "drop") {
                // drop the piece, summon next one
            } else if (cmd == "levelup") {
                // increment level if possible
            } else if (cmd == "leveldown") {
                // decrement level if possible
            } else if (cmd == "norandom") {
                string fileName;
                try {
                    cin >> fileName;
                } catch(...) {
                    // do something
                }
                // if level is 3/4 make it read from fileName
                // finish the try catch block above*****
            } else if (cmd == "random") {
                // if level is 3/4 restore randomness
            } else if (cmd == "sequence") {
                string fileName;
                try {
                    cin >> fileName;
                } catch(...) {
                    // do something**********
                }
                // execute sequence of commands in fileName
            } else if (cmd == "I") {
                // change the current block to I block
            } else if (cmd == "J") {
                // change the current block to J block
            } else if (cmd == "L") {
                // change the current block to L block
            } else if (cmd == "restart") {
                // clear the board and start new game
            } else if (cmd == "hint") {
                // display a hint
            }
        }
    } catch(...) {
        // do something about bad input********
    }
}