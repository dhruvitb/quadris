#include "level0.h"
#include "gamepiece.h"
#include <memory>
#include <iostream>
#include <fstream>
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
	//fileInput.open(fileName);
}
 
shared_ptr<GamePiece> Level0::generatePiece() {
	string s = generateString();
	return generatePieceFromString(s, false);
}

int Level0::getMyLevel() {
	return 0;
}
