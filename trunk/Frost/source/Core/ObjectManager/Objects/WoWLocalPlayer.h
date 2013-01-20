#ifndef _WOWLOCALPLAYER_H_
#define _WOWLOCALPLAYER_H_

#include "WoWPlayer.h"

class WoWLocalPlayer : public WoWPlayer {
public:
	WoWLocalPlayer(unsigned int objPtr);

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif