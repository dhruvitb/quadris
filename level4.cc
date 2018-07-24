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
    ++turnCount;
    if (turnCount == 5) {
        resetTurnCount();
        notifyObservers();
    }
    if (random) {
        vector<string> pieces{"I", "J", "L", "O", "S", "S", "T", "Z", "Z"};
        int size = pieces.size();
        int n = randomInt(size);
        return generatePieceFromString(pieces[n]);
    } else {
        string s = generateString();
        return generatePieceFromString(s);
    }
}


int Level4::getMyLevel() {
	return 4;
}