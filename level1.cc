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


Level1::Level1(): random{false}, myLevel{1} {}

shared_ptr<GamePiece> Level1::generatePiece(string s) {
    return make_shared<BlockO>(myLevel);
}
