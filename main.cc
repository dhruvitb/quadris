#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "grid.h"
#include "gamepiece.h"

using namespace std;

int main(int argc, char *argv[]) {
    string cmd;
    
    (void) argc; // REMOVE THESE ONCE YOU ACTUALLY MAKE USE OF THEM MAYBE LAMDLKANVJISFNLVKSJFDNVLKV
    (void) argv; // REMOVE THESE ONCE YOU ACTUALLY MAKE USE OF THEM MAYBE LAMDLKANVJISFNLVKSJFDNVLKV
    // FIND OUT HOW TO READ -ARG N TYPE COMMAND LINE ARGUMENTS
    unique_ptr<Grid> quadris = make_unique<Grid>();
    try {
        while (true) {
            cin >> cmd;
            if (cmd == "start") {
                quadris->print();
            }
            if (cmd == "left") {
                quadris->shiftPiece(Direction::Left);
                // move the current piece left
            } else if (cmd == "right") {
                quadris->shiftPiece(Direction::Right);
                // move the current piece right
            } else if (cmd == "down") {
                quadris->shiftPiece(Direction::Down);
                // move the current piece down
            } else if (cmd == "clockwise") {
                quadris->rotatePiece(Rotation::CW);
                // rotate 90 degrees clockwise
            } else if (cmd == "counterclockwise") {
                quadris->rotatePiece(Rotation::CCW);
                // rotate 90 degrees counterclockwise
            } else if (cmd == "drop") {
                quadris->drop();
                // drop the piece, summon next one
                quadris->getNextPiece();
            } else if (cmd == "levelup") {
                quadris->levelUp();
                // increment level if possible
            } else if (cmd == "leveldown") {
                quadris->levelDown();
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
            } else if (cmd == "end") {
                break;
            }
        }
    } catch(ios::failure &) {
        // do something about bad input********
    }
}