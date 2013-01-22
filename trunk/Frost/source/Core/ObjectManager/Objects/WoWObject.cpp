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

#include <Objects\WoWObject.h>
#include <CObjectManager.h>

WoWObject::WoWObject(unsigned int objPtr) {
	ObjectPointer = objPtr;
}

WoWObject::~WoWObject() {

}

int WoWObject::Type() {
	return Mem->Read<int>(ObjectPointer + Offsets::ObjectType);
}

unsigned long WoWObject::Guid() {
	return GetDescriptorField<unsigned long>(Descriptors::OBJECT_FIELD_GUID);
}

int WoWObject::Entry() {
	return GetDescriptorField<int>(Descriptors::OBJECT_FIELD_ENTRY);
}

CLocation WoWObject::Location() {
	CLocation l;

	l.X = Mem->Read<float>(ObjectPointer + Offsets::ObjectX);
	l.Y = Mem->Read<float>(ObjectPointer + Offsets::ObjectY);
	l.Z = Mem->Read<float>(ObjectPointer + Offsets::ObjectZ);

	return l;
}