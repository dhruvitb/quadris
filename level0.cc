#include "level0.h"
#include "gamepiece.h"
#include <memory>
#include "blockI.h"
#include "blockJ.h"
#include "blockL.h"
#include "blockO.h"
#include "blockS.h"
#include "blockT.h"
#include "blockZ.h"
#include "blockbomb.h"
using namespace std;

Level0::Level0(): random{false}, myLevel{0} {}
 
shared_ptr<GamePiece> Level0::generatePiece(string s) {
	//cout << "Piece has been generated" << endl;
	if (s == "I") {
		return make_shared<BlockI>(myLevel);
	} else if (s == "J") {
		return make_shared<BlockJ>(myLevel);
	} else if (s == "L") {
		return make_shared<BlockL>(myLevel);
	} else if (s == "O") {
		return make_shared<BlockO>(myLevel);
	} else if (s == "S") {
		return make_shared<BlockS>(myLevel);
	} else if (s == "Z") {
		return make_shared<BlockZ>(myLevel);
	} else { //b == "T"
		return make_shared<BlockT>(myLevel);
	}
}
