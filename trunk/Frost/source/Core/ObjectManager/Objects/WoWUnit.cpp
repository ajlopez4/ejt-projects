#include "WoWUnit.h"

WoWUnit::WoWUnit(unsigned int objPtr) : WoWObject(objPtr) {
	ObjectPointer = objPtr;
}

int WoWUnit::Level() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_LEVEL);
}

int WoWUnit::Health() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_HEALTH);
}

int WoWUnit::MaxHealth() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_MAXHEALTH);
}

int WoWUnit::Power() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_POWER) / 10;
}

int WoWUnit::MaxPower() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_MAXPOWER) / 10;
}

int WoWUnit::PowerType() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_DISPLAY_POWER);
}

unsigned int WoWUnit::getPtr() {
	return ObjectPointer;
}