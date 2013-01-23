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

#ifndef _CTABCONTROL_H_
#define _CTABCONTROL_H_

#include <Windows.h>
#include <CommCtrl.h>
#include <list>

using namespace std;

class CTabControl {
public:
	bool Create(HWND);
	bool AddTab(LPSTR);
	void RemoveTab(LPSTR);

	// Adds a control to the tab
	void AddControl(LPSTR, HWND);

	void SetSize(RECT);
	void SwitchTab(LPSTR, int);

	HWND Handle() { return hwnd; }

private:
	HWND hwnd;
	
	struct TabStruct {
		int pos;
		LPSTR text;
		list<HWND> children;
	};

	list<TabStruct> TabList;
};

#endif