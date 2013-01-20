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

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "AbstractWindow.h"

#include <list>

class MainWindow : public AbstractWindow {
public:
	MainWindow(const char* windowName, const char* className);

	virtual LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

	void Show() { ShowWindow(_hwnd, SW_SHOW); UpdateWindow(_hwnd); }

	bool CreateRest();
	void AddList(HWND);
public:
	HWND hwndTab, hwndTabObjects;
	HWND hwndLWContainers, hwndLWGameObjects, hwndLWItems, hwndLWPlayers, hwndLWUnits;
};

#endif