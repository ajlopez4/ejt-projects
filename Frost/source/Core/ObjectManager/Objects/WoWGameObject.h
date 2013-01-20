#ifndef _WOWGAMEOBJECT_H_
#define _WOWGAMEOBJECT_H_

#include "WoWObject.h"

class WoWGameObject : public WoWObject {
public:
	WoWGameObject(unsigned int objPtr);

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif