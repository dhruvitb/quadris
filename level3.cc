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
    return make_shared<BlockO>(myLevel);
}

int Level3::getMyLevel() {
	return 3;
}