#ifndef _WOWCONTAINER_H_
#define _WOWCONTAINER_H_

#include "WoWObject.h"

class WoWContainer : public WoWObject {
public:
	WoWContainer(unsigned int objPtr);

	int Slots();
	int NumSlots();

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif