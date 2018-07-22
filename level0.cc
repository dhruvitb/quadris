#include "level0.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

shared_ptr<GamePiece> Level0::generatePiece() {
    return make_shared<BlockO>();
}