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

	ApplicationHandle = NULL;

	return;
}