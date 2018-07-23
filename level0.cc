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

Level0::Level0() {
	random = false;
	fileName = "sequence.txt";
}
 
shared_ptr<GamePiece> Level0::generatePiece(string s) {
	//cout << "Piece has been generated" << endl;
}

int Level0::getMyLevel() {
	return 0;
}
