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
#include <list>

#include "../Common.h"
#include "../Core/ObjectManager/CObjectManager.h"

#include "AbstractWindow.h"
#include "CTabControl.h"
#include "CListControl.h"
#include "CButtonControl.h"
#include "CTextControl.h"

using namespace std;

#define TIMER_UPDATE_INFO	1001

class CSystem : public AbstractWindow {
public:

	CSystem(const char*, const char*);
	bool Initialize();
	void Shutdown();
	void Run();

	virtual LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

	void Show() { ShowWindow(_hwnd, SW_SHOW); UpdateWindow(_hwnd); }
private:

	CTabControl* MainTab;
	CTabControl* ObjectsTab;

	CListControl* ListPlayers;
	CListControl* ListUnits;
	CListControl* ListObjects;
	
	CTextControl* TextPlayerName;
	CTextControl* TextPlayerHealth;
	CTextControl* TextPlayerPower;
	CTextControl* TextPlayerLevel;
	
	CTextControl* TextTargetName;
	CTextControl* TextTargetHealth;
	CTextControl* TextTargetPower;
	CTextControl* TextTargetLevel;

	CObjectManager* ObjectManager;
};

#endif