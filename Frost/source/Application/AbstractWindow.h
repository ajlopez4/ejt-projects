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

#ifndef _ABSTRACTWINDOW_H_
#define _ABSTRACTWINDOW_H_

#include <Windows.h>

class AbstractWindow {
protected:
	HWND _hwnd, _hwndParent;
	LPCTSTR _windowName, _className;
	HINSTANCE _hInstance;
	DWORD _style, _styleEx;
	int _x, _y, _height, _width;
	HMENU _hMenu;

public:
	AbstractWindow() {}

	static LRESULT CALLBACK msgRouter(HWND, UINT, WPARAM, LPARAM);
	
	virtual LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM) = 0;

	virtual bool Create();
};

#endif