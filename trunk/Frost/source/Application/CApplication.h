#ifndef _CAPPLICATION_H_
#define _CAPPLICATION_H_

#include "../Common.h"

#include "../Core/ObjectManager/CObjectManager.h"

class CApplication {
public:
	bool Initialize();
	void Shutdown();

	CObjectManager* ObjectManager;
private:
};

#endif