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

#ifndef _COBJECTMANAGER_H_
#define _COBJECTMANAGER_H_

#include "../../Common.h"

#include "Objects\WoWContainer.h"
#include "Objects\WoWGameObject.h"
#include "Objects\WoWItem.h"
#include "Objects\WoWLocalPlayer.h"
#include "Objects\WoWObject.h"
#include "Objects\WoWPlayer.h"
#include "Objects\WoWUnit.h"

#include "Offsets/Constants.h"
#include "Offsets/Descriptors.h"
#include "Offsets/Offsets.h"

#include <list>

class CObjectManager {
public:

	bool Initialize();
	void Pulse();

	WoWLocalPlayer *GetLocalPlayer() { return LocalPlayer; }

private:
	unsigned int objectManager;
	unsigned long LocalPlayerGuid;

	void PurgeLists();

	WoWLocalPlayer *LocalPlayer;

	std::list<WoWContainer*>	ContainerList;
	std::list<WoWGameObject*>	GameObjectList;
	std::list<WoWItem*>			ItemList;
	std::list<WoWPlayer*>		PlayerList;
	std::list<WoWUnit*>			UnitList;
};

#endif