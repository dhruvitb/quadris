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

//returns the full string if input is unique or "" otherwise
string checkUniqueness(string input) { //assume command has no prefix (no number)
    //an array of possible commands
    vector<string> commands {"left", "right", "down", "clockwise", "counterclockwise", "drop",
    "levelup", "leveldown", "norandom", "random", "sequence", "I", "J", "L", "O", "S", "T", "Z", 
    "restart", "hint", "hold"};
    int matches = 0;
    int index; //the index for the matching command
    int size = commands.size();
    for (int i = 0; i < size; ++i) {
        if (commands[i].find(input) == 0) {
            ++matches;
            index = i;
        }
    }
    if (matches == 1) {
        return commands[index];
    }
    return "";
}

//mutates multiplier and returns the string part of the command
string updateMultiplier(string command, int &multiplier) {
    //updates multiplier
    int n = -1;
    string input;
    stringstream ss(command);
    ss >> n >> input; //n will become 0 if 0right or right (prefix and no prefix)
    if (n == 0 && (command.at(0) != '0')) { //no prefix so input needs the correct command
        stringstream ss(command);
        ss >> input;
    }
    //both n (multiplier) and input (user entered) reflect the actual command
    if (command.at(0) == '0') {
        multiplier = 0;
    } else if (isdigit(command.at(0))) { 
        multiplier = n;
    } //else the multiplier value doesn't get mutated (default value 1)
    string u = checkUniqueness(input); //u for unique
    /*if (u != "") { //shouldn't matter if the multiplier for these are changed
        if (u == "random" || u == "sequence" || u == "I" || u == "J" || u == "L" ||
            u == "O" || u == "S" || u == "T" || u == "Z" || u == "restart" || 
            u == "hint") {
            multiplier = 1; //these commands should only occur once
        }        
    }*/
    return input;
}

//makes sure colourScheme is valid
/*bool validColourScheme(string s) {
    bool valid = false;
    vector<string> library = {"Pastel", "Dark"};
    int size = library.size();
    for (int i; i < size; ++i) {
        if (library[i] == s) {
            valid = true;
            break;
        }
    }
    return valid;
}*/

/*
//checks if command contains action and ensures the command is valid
//there may be a multiplier
bool validCommand(string command, string action) {
    stringstream ss(command);

    int n = -1;
    string realCommand;

    if('0' <= command[0] && command[0] <= '9')
        ss >> n;

    ss >> realCommand;

    return (realCommand == action);
}
*/

//mutates multiplier
/*bool validCommand(string command, string action, int &multiplier) {
    bool contains = (command.find(action) != string::npos);
    if (!contains) {
        return false; 
    } //doesn't need to know if it is valid
    bool valid = false;
    stringstream ss(command);
    int n = -1;
    string s;
    ss >> n >> s; //n will become 0 if 0right or right
    //no digit in front (i.e. right)
    if (n == 0) {
        stringstream ss(command);
        ss >> s;
    }
    if (s == action) {
        valid = true;
        //actions where muliplier don't have an effect
        if (s == "random" || s == "sequence" || s == "I" || s == "J" || s == "L" ||
            s == "O" || s == "S" || s == "T" || s == "Z" || s == "restart" || 
            s == "hint") {
            return true; //contains && valid are both true
        }
        //case for 0right
        if (command.at(0) == '0') {
            multiplier = 0;
        } else if (isdigit(command.at(0))) { 
            multiplier = n;
        } 
        //if there is no digit in front (including negatives), multiplier doesn't change
        //default value is 1
    }
    return contains && valid;
}*/

bool gameOver() {
    string answer;
    bool restartGame;
    cout << "Game Over! Keep playing? Y/N" << endl;
    while (true) {
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.end(), ::tolower);
        if (answer == "y" || answer == "yes") {
            restartGame = true;
            break;
        } else if (answer == "n" || answer == "no") {
            restartGame = false;
            cout << "Thanks for playing!" << endl;
            break;
        }
    }
    return restartGame;
}


int main(int argc, char *argv[]) {
    unique_ptr<Grid> quadris = make_unique<Grid>();
    ifstream commandFile;
    string colourScheme = "Default";
    //startlevel is separate because scriptfile and seed depend on the level
    for (int i = 1; i < argc; ++i) {
        string option = argv[i];
        if (option == "-startlevel") {
            string lvl = argv[i+1];
            stringstream ss(lvl); //convert from string to int
            int x;
            ss >> x;
            if (x < 0 || x > 4) {
                cout << "Invalid level: " << x << endl;
            } else {
                quadris->updateLevel(x);
            }
            ++i;
            //change the level
        }
    }
    for (int i = 1; i < argc; ++i) {
        string option = argv[i];
        if (option == "-text") {
            quadris->changeTextOnly();
        } else if (option == "-graphics") {
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
        }  else if (option == "-colourscheme") {
            colourScheme = argv[i+1];
            ++i;
            //quadris->applyColourScheme(cscheme);
            //do something with colourscheme
        }
    }
    quadris->init(colourScheme); //considers command-line interface
    quadris->print();
    
    while (true) {
        string cmd;
        int multiplier = 1;

        //finds command from either file or keyboard
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

        //update multiplier for command
        string input = updateMultiplier(cmd, multiplier);
        
        //checks for uniqueness of command
        string temp = checkUniqueness(input);
        if (temp != "") {
            cmd = temp; //gives cmd the unique string, else the call is invalid
        }

        int repeat; //to protect against the user from putting in large numbers
        //prossess the command
        if (cmd == "left") {
            repeat = min(multiplier, 11);
            for (int i = 0; i < repeat; ++i) {
                quadris->shiftPiece(Direction::Left);
            }
            quadris->print();
            // move the current piece left
        } else if (cmd == "right") {
            repeat = min(multiplier, 11);
            for (int i = 0; i < repeat; ++i) {
                quadris->shiftPiece(Direction::Right);  
            }
            quadris->print();
            // move the current piece right
        } else if (cmd == "down") {
            repeat = min(multiplier, 18);
            for (int i = 0; i < repeat; ++i) {
                quadris->shiftPiece(Direction::Down);  
            }
            quadris->print();
            // move the current piece down
        } else if (cmd == "clockwise") {
            repeat = multiplier % 4;
            for (int i = 0; i < repeat; ++i) {
                quadris->rotatePiece(Rotation::CW);  
            }
            quadris->print();
            // rotate 90 degrees clockwise
        } else if (cmd == "counterclockwise") {
            repeat = multiplier % 4;
            for (int i = 0; i < repeat; ++i) {
                quadris->rotatePiece(Rotation::CCW);  
            }
            quadris->print();
            // rotate 90 degrees counterclockwise
        } else if (cmd == "drop") {
            bool lostGame = false;
            bool restartGame = false;
            repeat = min(multiplier, 15);
            for (int i = 0; i < multiplier; ++i) {
                if (!quadris->drop()) {
                    restartGame = gameOver();
                    lostGame = true;
                    break;
                }
            }
            if (lostGame) {
                if (restartGame) {
                    quadris->restart();
                } else {
                    break;
                }
            }
            quadris->print();
            // drop the piece, summon next one (the drop function handles this)
        } else if (cmd == "levelup") {
            repeat = min(LEVEL_MAX, multiplier);
            for (int i = 0; i < repeat; ++i) {
                quadris->levelUp();  
            }
            // increment level if possible
        } else if (cmd == "leveldown") {
            repeat = min(LEVEL_MAX, multiplier);
            for (int i = 0; i < repeat; ++i) {
                quadris->levelDown();  
            }
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
        } else if (cmd == "I" || cmd == "J" || cmd == "L" || cmd == "O" || cmd == "S" || 
            cmd == "T" || cmd == "Z") {
                bool isHeavy = false;
                int currentLevel = quadris->getCurrentLevel();
                if (currentLevel > 2) {
                    isHeavy = true;
                }
                quadris->replaceCurrentPiece(cmd, currentLevel, isHeavy);
                quadris->print();
                // change the current block to the block
        } else if (cmd == "restart") {
            // clear the board and start new game
            quadris->restart();
        } else if (cmd == "hint") {
            quadris->hint();
            quadris->print();
            // display a hint
        } else if (cmd == "hold") {
            if (!quadris->hold()) {
                if (gameOver()) {
                    quadris->restart();
                } else {
                    break;
                }
            }
            quadris->print();
        } else {
            cout << "Invalid command: " << cmd << endl;
        }
    }
}