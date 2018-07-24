#include "level.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"
#include "blockbomb.h"
using namespace std;

Level::Level() {
	srand(seed);
}

string Level::generateString() { //file has already been opened
	string s;
	fileInput >> s;
	if (s == "" || s == "\n") { //reached the EOF
		fileInput.close();
		fileInput.open(fileName);
		fileInput >> s;
	}
	return s;
}

shared_ptr<GamePiece> Level::generatePieceFromString(string s, bool isHeavy) {
    if (s == "I") {
		return make_shared<BlockI>(getMyLevel(), isHeavy);
	} else if (s == "J") {
		return make_shared<BlockJ>(getMyLevel(), isHeavy);
	} else if (s == "L") {
		return make_shared<BlockL>(getMyLevel(), isHeavy);
	} else if (s == "O") {
		return make_shared<BlockO>(getMyLevel(), isHeavy);
	} else if (s == "S") {
		return make_shared<BlockS>(getMyLevel(), isHeavy);
	} else if (s == "Z") {
		return make_shared<BlockZ>(getMyLevel(), isHeavy);
	} else { //s == "T"
		return make_shared<BlockT>(getMyLevel(), isHeavy);
	}
}

void Level::randomize() {
	if (random == true) {
		cout << "Level " << getMyLevel() << " is already random" << endl;
	} else {
		random = true;
		cout << "Random blocks have been restored" << endl;
	}
}

void Level::changeFileName (string f) {
    if (fileInput) {
		fileInput.close();
	}
	fileName = f;
	fileInput.open(fileName);
	if (!fileInput) {
		cout << "Invalid file: " << fileName << " :(" << endl;
	} else {
		random = false;
		cout << "New input file is: " << fileName << endl;
	}
}

void Level::changeSeed (int x) {
	seed = x;
	srand(seed);
}

void Level::resetTurnCount() {
    // does nothing normally (in level 4 it has purpose)
}

int Level::randomInt(int num) {
	int x = rand() % num;
	//cout << "random number is: " << x << endl;
	return x;
} 

LevelInfo Level::getInfo() const {
    return LevelInfo{true};
}

