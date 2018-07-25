#include "level4.h"
#include "gamepiece.h"
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"
#include "blockbomb.h"
#include <memory>
using namespace std;

Level4::Level4() {}

shared_ptr<GamePiece> Level4::generatePiece() {
    cout << "the turncount for brick is: " << turnCount << endl;
    if (turnCount == 5) { 
        resetTurnCount();
        notifyObservers();
    }
    if (random) {
        vector<string> pieces{"I", "J", "L", "O", "S", "S", "T", "Z", "Z"};
        int size = pieces.size();
        int n = randomInt(size);
        return generatePieceFromString(pieces[n], true);
    } else {
        string s = generateString();
        return generatePieceFromString(s, true);
    }
}

int Level4::getMyLevel() {
	return 4;
}

void Level4::resetTurnCount() {
    turnCount = 0;
}

void Level4::incrementTurnCount() {
    ++turnCount;
}