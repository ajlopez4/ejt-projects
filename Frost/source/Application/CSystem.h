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

#ifndef _CSYSTEM_H_
#define _CSYSTEM_H_

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>

#include "../Common.h"
#include "../Core/ObjectManager/CObjectManager.h"

#include "WindowClass.h"
#include "MainWindow.h"

#define	WM_OBJECTMANAGER_PULSE	3001

class CSystem {
public:
	bool Initialize();
	void Shutdown();
	void Run();

private:
	void InitializeWindows();
	void ShutdownWindows();

	bool done;

	WindowClass* wndClass;
	MainWindow* wnd;

	CObjectManager* ObjectManager;
};

static CSystem* ApplicationHandle = 0;

#endif