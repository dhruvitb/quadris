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

shared_ptr<GamePiece> Level::generatePieceFromString(string s) {
    if (s == "I") {
		return make_shared<BlockI>(getMyLevel());
	} else if (s == "J") {
		return make_shared<BlockJ>(getMyLevel());
	} else if (s == "L") {
		return make_shared<BlockL>(getMyLevel());
	} else if (s == "O") {
		return make_shared<BlockO>(getMyLevel());
	} else if (s == "S") {
		return make_shared<BlockS>(getMyLevel());
	} else if (s == "Z") {
		return make_shared<BlockZ>(getMyLevel());
	} else { //b == "T"
		return make_shared<BlockT>(getMyLevel());
	}
}

bool Level::getIsRandom() {
    return random;
}

void Level::randomize() {
    random = true;
}

void Level::changeFileName (string f) {
    fileName = f;
    random = false;
}

void Level::resetTurnCount() {
    turnCount = 0;
    // does nothing normally (in level 4 it has purpose)
}

void Level::openFile(std::string newFile) {
    fileInput.open(newFile);
}

LevelInfo Level::getInfo() const {
    return LevelInfo{true};
}

