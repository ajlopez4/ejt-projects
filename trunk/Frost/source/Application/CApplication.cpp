#include "CApplication.h"

bool CApplication::Initialize() {
	Mem = new CMemory;

	if(!Mem)
		return false;

	if(!Mem->Initialize())
		return false;

	ObjectManager = new CObjectManager;

	if(!ObjectManager)
		return false;

	if(!ObjectManager->Initialize())
		return false;

	ObjectManager->Pulse(); // Force pulse to get local player

	return true;
}

void CApplication::Shutdown() {
	if(Mem) {
		delete Mem;
		Mem = 0;
	}

	if(ObjectManager) {
		delete ObjectManager;
		ObjectManager = 0;
	}

	return;
}