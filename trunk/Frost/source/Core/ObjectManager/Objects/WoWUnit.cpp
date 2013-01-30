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

#include <Objects\WoWUnit.h>
#include <ObjectManager\CObjectManager.h>

WoWUnit::WoWUnit(unsigned int objPtr) : WoWObject(objPtr) {
	ObjectPointer = objPtr;
}

CLocation WoWUnit::Location() {
	CLocation l;

	l.X = Mem.Read<float>(ObjectPointer + Offsets::UnitX);
	l.Y = Mem.Read<float>(ObjectPointer + Offsets::UnitY);
	l.Z = Mem.Read<float>(ObjectPointer + Offsets::UnitZ);

	return l;
}

float WoWUnit::Facing() {
	return Mem.Read<float>(ObjectPointer + Offsets::UnitR);
}

unsigned long WoWUnit::CharmedBy() {
	return GetDescriptorField<unsigned long>(Descriptors::UNIT_FIELD_CHARMED_BY);
}

unsigned long WoWUnit::SummonedBy() {
	return GetDescriptorField<unsigned long>(Descriptors::UNIT_FIELD_SUMMONED_BY);
}

unsigned long WoWUnit::CreatedBy() {
	return GetDescriptorField<unsigned long>(Descriptors::UNIT_FIELD_CREATED_BY);
}

bool WoWUnit::Critter() {
	return GetDescriptorField<bool>(Descriptors::UNIT_FIELD_CRITTER);
}

int WoWUnit::Level() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_LEVEL);
}

int WoWUnit::BaseHealth() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_BASE_HEALTH);
}

int WoWUnit::Health() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_HEALTH);
}

int WoWUnit::MaxHealth() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_MAXHEALTH);
}

int WoWUnit::HealthPercentage() {
	if(Health() == 0) return 0; else return (100 * Health()) / MaxHealth();
}

int WoWUnit::BaseMana() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_BASE_MANA);
}

int WoWUnit::Power() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_POWER);
}

int WoWUnit::MaxPower() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_MAXPOWER);
}

int WoWUnit::PowerPercentage() {
	if(MaxPower() == 0) return 0; else return (100 * Power()) / MaxPower();
}

WoWPowerType::Enum WoWUnit::PowerType() {
	unsigned int overridePowerId = GetDescriptorField<unsigned int>(Descriptors::UNIT_FIELD_OVERRIDE_DISPLAY_POWER_ID);
	if(overridePowerId == 0)
		return (WoWPowerType::Enum)(GetDescriptorField<unsigned int>(Descriptors::UNIT_FIELD_DISPLAY_POWER) >> 24);
	else
		return (WoWPowerType::Enum)overridePowerId;
}

LPSTR WoWUnit::PowerTypeName() {
	switch(PowerType()) {
		case 0: return "Mana";
		case 1: return "Rage";
		case 2: return "Focus";
		case 3: return "Chi";
		case 4: return "Runes";
		case 5: return "Runic Power";
		case 6: return "Soulshards";
		case 7: return "Eclipse";
		case 8: return "Holy Power";
		case 9: return "Alternate";
		case 11: return "Dark Force";
		case 12: return "Light Force";
		case 13: return "Shadow Orbs";
		case 14: return "Burning Embers";
		case 15: return "Demonic Fury";
		default: return "";
	}
}

WoWRace::Enum WoWUnit::Race() {
	return (WoWRace::Enum)(GetDescriptorField<unsigned int>(Descriptors::UNIT_FIELD_DISPLAY_POWER) & 0xFF);
}

LPSTR WoWUnit::RaceName() {
	switch(Race()) {
		case 1: return "Human";
		case 2: return "Orc";
		case 3: return "Dwarf";
		case 4: return "Night Elf";
		case 5: return "Undead";
		case 6: return "Tauren";
		case 7: return "Gnome";
		case 8: return "Troll";
		case 9: return "Goblin";
		case 11: return "Blood Elf";
		case 12: return "Draenei";
		case 22: return "Worgen";
		case 24: 
		case 25: 
		case 26: return "Pandaren";
		default: return "";
	}
}

WoWClass::Enum WoWUnit::Class() {
	return (WoWClass::Enum)((GetDescriptorField<unsigned int>(Descriptors::UNIT_FIELD_DISPLAY_POWER) >> 8) & 0xFF);
}

LPSTR WoWUnit::ClassName() {
	switch(Class()) {
		case 0: return "None";
		case 1: return "Warrior";
		case 2: return "Paladin";
		case 3: return "Hunter";
		case 4: return "Rogue";
		case 5: return "Priest";
		case 6: return "Death Knight";
		case 7: return "Shaman";
		case 8: return "Mage";
		case 9: return "Warlock";
		case 10: return "Monk";
		case 11: return "Druid";
		default: return "";
	}
}

WoWGender::Enum WoWUnit::Gender() {
	return (WoWGender::Enum)((GetDescriptorField<unsigned int>(Descriptors::UNIT_FIELD_DISPLAY_POWER) >> 16) & 0xFF);
}

LPSTR WoWUnit::GenderName() {
	switch(Gender()) {
		case 0: return "Male";
		case 1: return "Female";
		case 2: return "Unknown";
		default: return "";
	}
}

bool WoWUnit::Dead() {
	return (Health() <= 1);
}

string WoWUnit::Name() {
	unsigned int u1 = Mem.Read<unsigned int>(ObjectPointer + Offsets::UnitName1);
	unsigned int u2 = Mem.Read<unsigned int>(u1 + Offsets::UnitName2);
	string ret = Mem.ReadString(u2, 32);
	return ret;
}

WoWUnit* WoWUnit::Target() { // TODO: Doesn't get players.
	// First check units
	for each(WoWUnit* target in ObjectManager.GetUnits()) {
		if(target->Guid() == TargetGuid())
			return target;
	}
	
	// Check if it could be a player
	for each(WoWPlayer* target in ObjectManager.GetPlayers()) {
		if(target->Guid() == TargetGuid())
			return target;
	}

	return NULL;
}

WoWUnit* WoWUnit::Pet() {
	for each(WoWUnit* unit in ObjectManager.GetUnits()) {
		if(unit->SummonedBy() == this->Guid())
			return unit;
	}

	return NULL;
}

unsigned long WoWUnit::TargetGuid() {
	return GetDescriptorField<unsigned long>(Descriptors::UNIT_FIELD_TARGET);
}

int WoWUnit::DisplayID() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_DISPLAY_ID);
}

int WoWUnit::MountDisplayID() {
	return GetDescriptorField<int>(Descriptors::UNIT_FIELD_MOUNT_DISPLAY_ID);
}

bool WoWUnit::Mounted() {
	return (MountDisplayID() > 0);
}

/* TODO: Need a function to check for dynamic flag before we can implement these
bool WoWUnit::Tagged() {
	
}

bool WoWUnit::TaggedByMe() {
	
}

bool WoWUnit::TaggedByOther() {
	
} */

bool WoWUnit::CastingBar() {
	return Mem.Read<bool>(ObjectPointer + Offsets::UnitCast);
}

bool WoWUnit::Casting() {
	return (CastingBar() || ChanneledCasting());
}

bool WoWUnit::ChanneledCasting() {
	return Mem.Read<bool>(ObjectPointer + Offsets::UnitChannel);
}