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

#include <Objects\WoWLocalPlayer.h>

WoWLocalPlayer::WoWLocalPlayer(unsigned int objPtr) : WoWPlayer(objPtr) {
	ObjectPointer = objPtr;
}

unsigned int WoWLocalPlayer::TargetGuid() {
	return Mem.Read<unsigned int>(Offsets::Target);
}

int WoWLocalPlayer::Experience() {
	return Mem.Read<int>(Descriptors::PLAYER_FIELD_XP);
}

int WoWLocalPlayer::ExperienceToLevel() {
	return Mem.Read<int>(Descriptors::PLAYER_FIELD_NEXT_LEVEL_XP);
}

int WoWLocalPlayer::ExperienceRested() {
	return Mem.Read<int>(Descriptors::PLAYER_FIELD_REST_STATE_BONUS_POOL);
}

string WoWLocalPlayer::Name() {
	return Mem.ReadString(Mem.dwBaseAddress + Offsets::PlayerName, 32);
}

bool WoWLocalPlayer::InGame() {
	return Mem.Read<bool>(Mem.dwBaseAddress + Offsets::InGame);
}