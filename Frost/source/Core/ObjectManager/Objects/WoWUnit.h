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

#ifndef _WOWUNIT_H_
#define _WOWUNIT_H_

#include <Objects\WoWObject.h>

class WoWUnit : public WoWObject {
public:
	WoWUnit(unsigned int objPtr);
	
	virtual string Name();
	virtual CLocation Location();
	float Facing();
	unsigned long CharmedBy();
	unsigned long SummonedBy();
	unsigned long CreatedBy();
	bool Critter();
	int Level();
	int BaseHealth();
	int Health();
	int MaxHealth();
	int HealthPercentage();
	bool Dead();
	int BaseMana(); // BaseMana or BasePower???
	int Power();
	int MaxPower();
	int PowerPercentage();
	LPSTR PowerType();
	WoWUnit Target();
	WoWUnit Pet();
	unsigned long TargetGuid();
	int DisplayID();
	int MountDisplayID();
	bool Mounted();
	bool Tagged();
	bool TaggedByMe();
	bool TaggedByOther();
	bool CastingBar();
	bool Casting();
	bool ChanneledCasting();

	virtual bool IsValid() { return (ObjectPointer != 0); }

private:
	unsigned int ObjectPointer;
};

#endif