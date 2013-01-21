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

#include "WoWPlayer.h"

WoWPlayer::WoWPlayer(unsigned int objPtr) : WoWUnit(objPtr) {
	ObjectPointer = objPtr;
}

string WoWPlayer::Name() {
	unsigned long mask, base_, offset, current, myGUID, currentGUID;

	mask = Mem->Read<unsigned int>(Mem->dwBaseAddress + Offsets::nameStorePtr + Offsets::nameMaskOffset);
	base_ = Mem->Read<unsigned int>(Mem->dwBaseAddress + Offsets::nameStorePtr + Offsets::nameBaseOffset);

	myGUID =  this->Guid() & 0xFFFFFFFF;
	offset = 12 * (mask & myGUID);

	current = Mem->Read<unsigned int>((unsigned int)(base_ + offset + 8));
	offset = Mem->Read<unsigned int>((unsigned int)(base_ + offset));
	if((current & 0x1) == 0x1)
		return "";

	currentGUID = Mem->Read<unsigned int>((unsigned int)current);

	while(currentGUID != myGUID) {
		current = Mem->Read<unsigned int>((unsigned int)(current + offset + 4));
		if((current & 0x1) == 0x1)
			return "";
		currentGUID = Mem->Read<unsigned int>((unsigned int)(current));
	}

	return Mem->ReadString((unsigned int)(current + Offsets::nameStringOffset));
}

unsigned int WoWPlayer::getPtr() {
	return ObjectPointer;
}