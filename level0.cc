#include "level0.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

Level0::Level0(): random{false}, myLevel{0} {}
 
shared_ptr<GamePiece> Level0::generatePiece() {
    return make_shared<BlockO>(myLevel);
}
