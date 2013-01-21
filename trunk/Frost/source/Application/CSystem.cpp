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

#include "CSystem.h"

bool CSystem::Initialize() {
	InitializeWindows();

	Mem = new CMemory;
	if(!Mem || !Mem->Initialize())
		return false;

	ObjectManager = new CObjectManager;
	if(!ObjectManager || !ObjectManager->Initialize())
		return false;

	ObjectManager->Pulse(); // Force pulse to get local player

	return true;
}

void CSystem::Shutdown() {
	if(Mem) {
		delete Mem;
		Mem = 0;
	}

	if(ObjectManager) {
		delete ObjectManager;
		ObjectManager = 0;
	}

	ShutdownWindows();

	done = true;

	return;
}

void CSystem::Run() {
	MSG msg;
	done = false;

	ZeroMemory(&msg, sizeof(MSG));

	while(GetMessage(&msg, NULL, 0, 0) > 0 && !done) {
		if(msg.message == WM_TIMER) {
			if(msg.wParam == TIMER_PULSE && ObjectManager->GetLocalPlayer()->InGame()) {
				ObjectManager->Pulse();

				wnd->ListPlayers->Clear();

				list<WoWPlayer*> playerList = ObjectManager->GetPlayerList();

				for(list<WoWPlayer*>::iterator it = playerList.begin(); 
					it != playerList.end(); it++) {

					char guid[64] = {0};
					char name[64] = {0};
					char health[64] = {0};
					char power[64] = {0};
					char level[64] = {0};
					
					sprintf_s(guid, "%d", (*it)->Guid());
					sprintf_s(name, "%s", (*it)->Name().c_str());
					sprintf_s(health, "%d", (*it)->Health());
					sprintf_s(power, "%d", (*it)->Power());
					sprintf_s(level, "%d", (*it)->Level());

					LPSTR row[] = {
						guid, name, health, power, level
					};

					wnd->ListPlayers->AddRow(row);
				}

				wnd->ListUnits->Clear();

				list<WoWUnit*> unitList = ObjectManager->GetUnitList();

				for(list<WoWUnit*>::iterator it = unitList.begin(); 
					it != unitList.end(); it++) {

					char guid[64] = {0};
					char name[64] = {0};
					char health[64] = {0};
					char power[64] = {0};
					char level[64] = {0};
					
					sprintf_s(guid, "%d", (*it)->Guid());
					sprintf_s(name, "%s", (*it)->Name().c_str());
					sprintf_s(health, "%d", (*it)->Health());
					sprintf_s(power, "%d", (*it)->Power());
					sprintf_s(level, "%d", (*it)->Level());

					LPSTR row[] = {
						guid, name, health, power, level
					};

					wnd->ListUnits->AddRow(row);
				}
			}
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return;
}

void CSystem::InitializeWindows() {
	wndClass = new WindowClass(GetModuleHandle(NULL), "FrostWndClass");
	wndClass->Register();

	wnd = new MainWindow("Frost - Simple World of Warcraft Bot", wndClass->className());
	wnd->Create();
	wnd->Show();

	return;
}

void CSystem::ShutdownWindows() {
	if(wndClass) {
		delete wndClass;
		wndClass = 0;
	}

	if(wnd) {
		delete wnd;
		wnd = 0;
	}

	return;
}