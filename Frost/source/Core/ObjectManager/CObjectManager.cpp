#include "CObjectManager.h"

bool CObjectManager::Initialize() {
	objectManager = Mem->Read<unsigned int>(Mem->Read<unsigned int>(Mem->dwBaseAddress + Offsets::ObjectMgr) + Offsets::CurMgr);

	LocalPlayerGuid = Mem->Read<unsigned long>(objectManager + Offsets::LocalGuid);
	LocalPlayer = NULL;

	return true;
}

void CObjectManager::Pulse() {
	PurgeLists();

	unsigned int currObj = Mem->Read<unsigned int>(objectManager + Offsets::FirstObject);

	std::list<unsigned int> objects;

	while(currObj != 0 && (currObj & 1) == 0) {
		objects.push_back(currObj);
		currObj = Mem->Read<unsigned int>(currObj + Offsets::NextObject);
	}

	for each(unsigned int obj in objects) {
		WoWObject * definedObj = new WoWObject(obj);

		switch(definedObj->Type()) {
			case Constants::WoWObject::Container:
				ContainerList.push_back(new WoWContainer(obj));
				break;
			case Constants::WoWObject::GameObject:
				GameObjectList.push_back(new WoWGameObject(obj));
				break;
			case Constants::WoWObject::Item:
				ItemList.push_back(new WoWItem(obj));
				break;
			case Constants::WoWObject::Player:
				PlayerList.push_back(new WoWPlayer(obj));
				if(definedObj->Guid() == LocalPlayerGuid && LocalPlayer == NULL)
					LocalPlayer = new WoWLocalPlayer(obj);
				break;
			case Constants::WoWObject::Unit:
				UnitList.push_back(new WoWUnit(obj));
				break;
		}

		delete definedObj;
		definedObj = 0;
	}
}

void CObjectManager::PurgeLists() {
	for(std::list<WoWContainer*>::iterator it = ContainerList.begin(); it != ContainerList.end(); it++) {
		delete (*it);
		(*it) = 0;
	}

	ContainerList.clear();

	for(std::list<WoWGameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); it++) {
		delete (*it);
		(*it) = 0;
	}

	GameObjectList.clear();

	for(std::list<WoWItem*>::iterator it = ItemList.begin(); it != ItemList.end(); it++) {
		delete (*it);
		(*it) = 0;
	}

	ItemList.clear();

	for(std::list<WoWPlayer*>::iterator it = PlayerList.begin(); it != PlayerList.end(); it++) {
		delete (*it);
		(*it) = 0;
	}

	PlayerList.clear();

	for(std::list<WoWUnit*>::iterator it = UnitList.begin(); it != UnitList.end(); it++) {
		delete (*it);
		(*it) = 0;
	}

	UnitList.clear();
}