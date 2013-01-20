/*	Frost Open-Source World of Warcraft Bot
	Copyright (C) 2013 https://code.google.com/p/ejt-projects/

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>. */

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

std::string WoWUnit::Name() {
	unsigned int u1 = Mem->Read<unsigned int>(ObjectPointer + Offsets::UnitName1);
	unsigned int u2 = Mem->Read<unsigned int>(u1 + Offsets::UnitName2);
	std::string ret = Mem->ReadString(u2);
	return ret;
}

unsigned int WoWUnit::getPtr() {
	return ObjectPointer;
}