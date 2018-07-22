#include "level4.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

shared_ptr<GamePiece> Level4::generatePiece() {
    ++turnCount;
    if (turnCount == 5) {
        resetTurnCount();
    }
    return make_shared<BlockO>();
}

void Level4::resetTurnCount() {
    turnCount = 0;
}