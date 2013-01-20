#ifndef _WOWPLAYER_H_
#define _WOWPLAYER_H_

#include "WoWUnit.h"

class WoWPlayer : public WoWUnit {
public:
	WoWPlayer(unsigned int objPtr);

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif