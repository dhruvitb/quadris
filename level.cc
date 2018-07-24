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

string Level::generateString() {
	string s;
	if (!(fileInput.is_open())) {
		fileInput.open(fileName);
	}
	fileInput >> s;
	if (s == "" || s == "\n") {
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
	} else { //b == "T"
		return make_shared<BlockT>(getMyLevel(), isHeavy);
	}
}

void Level::randomize() {
    random = true;
}

void Level::changeFileName (string f) {
    fileName = f;
    random = false;
}

void Level::resetTurnCount() {
    // does nothing normally (in level 4 it has purpose)
}

int Level::randomInt(int num) {
	int x = rand() % num;
	return x;
} 

LevelInfo Level::getInfo() const {
    return LevelInfo{true};
}

