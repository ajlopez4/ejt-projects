#ifndef _WOWITEM_H_
#define _WOWITEM_H_

#include "WoWObject.h"

class WoWItem : public WoWObject {
public:
	WoWItem(unsigned int objPtr);

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif