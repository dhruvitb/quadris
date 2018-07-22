#include "level.h"
using namespace std;

void Level::resetTurnCount() {
    // does nothing normally (in level 4 it has purpose)
}

LevelInfo Level::getInfo() const {
    return LevelInfo{true};
}
