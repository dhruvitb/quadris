#include "level2.h"
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

Level2::Level2() {}

shared_ptr<GamePiece> Level2::generatePiece() {
    return make_shared<BlockO>(myLevel);
}

int Level2::getMyLevel() {
	return 2;
}
