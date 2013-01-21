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

	int Level();

	int Health();
	int MaxHealth();
	int HealthPercentage();
	int Power();
	int MaxPower();
	int PowerPercentage();
	LPSTR PowerType();

	bool Dead();

	virtual string Name();

	WoWUnit Target();
	unsigned long TargetGuid();

private:
	unsigned int ObjectPointer;
};

#endif