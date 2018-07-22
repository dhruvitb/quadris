#include "level3.h"
#include "gamepiece.h"
#include "blockO.h"
#include <memory>
using namespace std;

Level3::Level3(): random{false}, myLevel{3} {
    
}

shared_ptr<GamePiece> Level3::generatePiece(string s) {
    return make_shared<BlockO>(myLevel);
}
