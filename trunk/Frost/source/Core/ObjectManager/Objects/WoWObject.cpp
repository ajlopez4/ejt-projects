#include "WoWObject.h"

WoWObject::WoWObject(unsigned int objPtr) {
	ObjectPointer = objPtr;
}

WoWObject::~WoWObject() {

}

int WoWObject::Type() {
	return Mem->Read<int>(ObjectPointer + 0x10);
}

unsigned long WoWObject::Guid() {
	return GetDescriptorField<unsigned long>(Descriptors::OBJECT_FIELD_GUID);
}

unsigned int WoWObject::getPtr() {
	return ObjectPointer;
}