#include "level3.h"
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

Level3::Level3() {}

shared_ptr<GamePiece> Level3::generatePiece() {
    if (random) {
        vector<string> pieces{"I", "J", "L", "O", "S", "S", "T", "Z", "Z"};
        int size = pieces.size();
        int n = randomInt(size);
        return generatePieceFromString(pieces[n], true);
    } else { // do not randomly generate pieces
        string s = generateString();
        return generatePieceFromString(s, true);
    }
}

int Level3::getMyLevel() {
	return 3;
}
