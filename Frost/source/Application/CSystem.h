#ifndef _CSYSTEM_H_
#define _CSYSTEM_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>

#include "CApplication.h"

#include "../Resources/resource.h"

#define	WM_OBJECTMANAGER_PULSE	3001

class CSystem {
public:
	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK msgRouter(HWND, UINT, WPARAM, LPARAM);

private:
	void InitializeWindows();
	void ShutdownWindows();

	bool done;

	LPCSTR m_className;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	CApplication* m_Application;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static CSystem* ApplicationHandle = 0;

#endif