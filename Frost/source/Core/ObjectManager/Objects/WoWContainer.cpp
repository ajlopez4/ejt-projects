#include "WoWContainer.h"

WoWContainer::WoWContainer(unsigned int objPtr) : WoWObject(objPtr) {
	ObjectPointer = objPtr;
}

int WoWContainer::Slots() {
	return GetDescriptorField<int>(Descriptors::CONTAINER_FIELD_SLOTS);
}

int WoWContainer::NumSlots() {
	return GetDescriptorField<int>(Descriptors::CONTAINER_FIELD_NUM_SLOTS);
}

unsigned int WoWContainer::getPtr() {
	return ObjectPointer;
}