#include "level2.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

shared_ptr<GamePiece> Level2::generatePiece() {
    return make_shared<BlockO>();
}