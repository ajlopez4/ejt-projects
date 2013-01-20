#ifndef _WOWUNIT_H_
#define _WOWUNIT_H_

#include "WoWObject.h"

class WoWUnit : public WoWObject {
public:
	WoWUnit(unsigned int objPtr);

	int Level();
	int Health();
	int MaxHealth();
	int Power();
	int MaxPower();
	int PowerType();

	unsigned int getPtr();

private:
	unsigned int ObjectPointer;
};

#endif