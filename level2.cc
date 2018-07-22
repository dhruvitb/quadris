#include "level2.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

Level2::Level2(): random{false}, myLevel{2} {}

shared_ptr<GamePiece> Level2::generatePiece() {
    return make_shared<BlockO>();
}
