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

#include <Windows.h>

#include <Application\WindowClass.h>
#include <Application\CSystem.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WindowClass wndClass(hInstance, "FrostWndClass");

	if(!wndClass.Register()) {
		MessageBox(NULL, "Failed to register window class!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	CSystem System("Frost - Simple World of Warcraft Bot", wndClass.className());

	if(!System.Create()) {
		MessageBox(NULL, "System.Create() returned false", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	System.Show();

	if(System.Initialize()) {
		System.Run();
	} else {
		MessageBox(NULL, "System.Initialize() returned false", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	return 0;
}