#include "Application\CSystem.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	CSystem* System;

	System = new CSystem;
	if(!System)
		return 0;

	if(System->Initialize())
		System->Run();

	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}