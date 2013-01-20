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