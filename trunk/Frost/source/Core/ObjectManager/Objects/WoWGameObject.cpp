#include "WoWGameObject.h"

WoWGameObject::WoWGameObject(unsigned int objPtr) : WoWObject(objPtr) {
	ObjectPointer = objPtr;
}

unsigned int WoWGameObject::getPtr() {
	return ObjectPointer;
}