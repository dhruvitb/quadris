#include "level4.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

Level4::Level4(): random{false}, myLevel{4}, turnCount{0} {

}

shared_ptr<GamePiece> Level4::generatePiece(string s) {
    ++turnCount;
    if (turnCount == 5) {
        resetTurnCount();
    }
    return make_shared<BlockO>(myLevel);
}

void Level4::resetTurnCount() {
    turnCount = 0;
}
