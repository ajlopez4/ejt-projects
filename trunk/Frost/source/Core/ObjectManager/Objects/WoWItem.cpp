#include "WoWItem.h"

WoWItem::WoWItem(unsigned int objPtr) : WoWObject(objPtr) {
	ObjectPointer = objPtr;
}

unsigned int WoWItem::getPtr() {
	return ObjectPointer;
}