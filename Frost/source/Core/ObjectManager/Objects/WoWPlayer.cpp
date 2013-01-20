#include "WoWPlayer.h"

WoWPlayer::WoWPlayer(unsigned int objPtr) : WoWUnit(objPtr) {
	ObjectPointer = objPtr;
}

unsigned int WoWPlayer::getPtr() {
	return ObjectPointer;
}