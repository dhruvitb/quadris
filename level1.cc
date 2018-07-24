#include "level1.h"
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


Level1::Level1() {}

shared_ptr<GamePiece> Level1::generatePiece() {
    vector<string> pieces{"I", "I", "J", "J", "L", "L", "O", "O", 
    "S", "T", "T", "Z"};
    int size = pieces.size();
    int n = randomInt(size);
    return generatePieceFromString(pieces[n]);
}

int Level1::getMyLevel() {
	return 1;
}