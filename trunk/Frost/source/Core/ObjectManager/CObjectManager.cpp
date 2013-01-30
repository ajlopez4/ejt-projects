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

#include <CObjectManager.h>

CObjectManager ObjectManager;
WoWLocalPlayer* Me;

bool CObjectManager::Initialize() {
	objectManager = Mem.Read<unsigned int>(Mem.Read<unsigned int>(Mem.dwBaseAddress + Offsets::ObjectMgr) + Offsets::CurMgr);

	LocalPlayerGuid = Mem.Read<unsigned long>(objectManager + Offsets::LocalGuid);
	Me = NULL;

	return true;
}

void CObjectManager::Pulse() {
	PurgeLists();

	unsigned int currObj = Mem.Read<unsigned int>(objectManager + Offsets::FirstObject);

	std::list<unsigned int> objects;

	while(currObj != 0 && (currObj & 1) == 0) {
		objects.push_back(currObj);
		currObj = Mem.Read<unsigned int>(currObj + Offsets::NextObject);
	}

	for each(unsigned int obj in objects) {
		WoWObject * definedObj = new WoWObject(obj);

		switch(definedObj->Type()) {
			case WoWObjectType::Container:
				ContainerList.push_back(new WoWContainer(obj));
				break;
			case WoWObjectType::GameObject:
				GameObjectList.push_back(new WoWGameObject(obj));
				break;
			case WoWObjectType::Item:
				ItemList.push_back(new WoWItem(obj));
				break;
			case WoWObjectType::Player:
				PlayerList.push_back(new WoWPlayer(obj));
				if(definedObj->Guid() == LocalPlayerGuid && Me == NULL)
					Me = new WoWLocalPlayer(obj);
				break;
			case WoWObjectType::Unit:
				UnitList.push_back(new WoWUnit(obj));
				break;
		}

		delete definedObj; // Delete the object
		definedObj = 0; // Avoid memleaks
	}
}

void CObjectManager::PurgeLists() {
	while(!ContainerList.empty()) delete ContainerList.back(), ContainerList.pop_back();
	while(!GameObjectList.empty()) delete GameObjectList.back(), GameObjectList.pop_back();
	while(!ItemList.empty()) delete ItemList.back(), ItemList.pop_back();
	while(!PlayerList.empty()) delete PlayerList.back(), PlayerList.pop_back();
	while(!UnitList.empty()) delete UnitList.back(), UnitList.pop_back();
}