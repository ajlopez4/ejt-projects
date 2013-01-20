#include "WoWLocalPlayer.h"

WoWLocalPlayer::WoWLocalPlayer(unsigned int objPtr) : WoWPlayer(objPtr) {
	ObjectPointer = objPtr;
}

unsigned int WoWLocalPlayer::getPtr() {
	return ObjectPointer;
}